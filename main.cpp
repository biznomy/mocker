#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/ThreadPool.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include "Poco/Path.h"
#include <iostream>

#include "TempData.h"
#define SAMPLE_INTERVAL  (1000 * 1000)

using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Path;
Path p;

class PageRequestHandler: public HTTPRequestHandler
	/// Return a HTML document with some JavaScript creating
	/// a WebSocket connection.
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");
		std::ostream& ostr = response.send();
		Poco::JSON::Object testObject;
		TempData::instance()->getData(testObject);
		std::stringstream ss;
		testObject.stringify(ss, 2, 2);

		Poco::AutoPtr<Poco::Util::JSONConfiguration> js = new Poco::Util::JSONConfiguration(ss);
		cout << "Remove Chest " << endl;
		js->remove("wirelessTrue.wireless.chest");
		cout << js->getString("wirelessTrue") << endl;

		ostr << ss.str() << endl;
	}
};


class WebSocketRequestHandler: public HTTPRequestHandler
	/// Handle a WebSocket connection.
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response){
		Application& app = Application::instance();
		try
		{
			WebSocket ws(request, response);
			app.logger().information("WebSocket connection established.");
			char buffer[1024];
			int flags;
			int n;
			n = ws.receiveFrame(buffer, sizeof(buffer), flags);
			do{

				Poco::JSON::Object testObject;
				TempData::instance()->getData(testObject);
				std::stringstream ss;
				testObject.stringify(ss, 2, 2);
				ws.sendFrame(ss.str().c_str(), ss.str().size(), flags);
				usleep(SAMPLE_INTERVAL);

			}while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
			app.logger().information("WebSocket connection closed.");
		}
		catch (WebSocketException& exc)
		{
			app.logger().log(exc);
			switch (exc.code())
			{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}
	}
};


class RequestHandlerFactory: public HTTPRequestHandlerFactory{
public:
	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		Application& app = Application::instance();
		app.logger().information("Request from "
			+ request.clientAddress().toString()
			+ ": "
			+ request.getMethod()
			+ " "
			+ request.getURI()
			+ " "
			+ request.getVersion());

		for (HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it)
		{
			app.logger().information(it->first + ": " + it->second);
		}

		if(request.find("Upgrade") != request.end() && Poco::icompare(request["Upgrade"], "websocket") == 0)
			return new WebSocketRequestHandler;
		else
			return new PageRequestHandler;
	}
};


class WebSocketServer: public Poco::Util::ServerApplication{
public:
	WebSocketServer(): _helpRequested(false)
	{
	}

	~WebSocketServer()
	{
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A sample HTTP server supporting the WebSocket protocol.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args){

		if (_helpRequested){

			displayHelp();

		}else{

			// get parameters from configuration file
			unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 8383);

			// set-up a server socket
			ServerSocket svs(port);


			HTTPServerParams::Ptr params = new HTTPServerParams;
			params->setMaxQueued(1);
			params->setMaxThreads(1);

			// set-up a HTTPServer instance
			HTTPServer srv(new RequestHandlerFactory, svs, params);
			// start the HTTPServer
			srv.start();
			// wait for CTRL-C or kill
			waitForTerminationRequest();
			// Stop the HTTPServer
			srv.stop();
		}
		return Application::EXIT_OK;
	}

private:
	bool _helpRequested;
};


POCO_SERVER_MAIN(WebSocketServer)
