#using <System.dll>

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;


void main()
{
	try
	{
		// Set the TcpListener on port 13000.
		Int32 port = 13000;
		IPAddress^ localAddr = IPAddress::Parse("127.0.0.1");

		TcpListener^ server = gcnew TcpListener(localAddr, port);

		// Start listening for client requests.
		server->Start();

		// Buffer for reading data
		array<Byte>^ bytes = gcnew array<Byte>(256);
		String^ data = nullptr;

		// Enter the listening loop.
		while (true)
		{
			Console::WriteLine("Waiting for a messages... ");

			TcpClient^ client = server->AcceptTcpClient();
			Console::WriteLine("Connected!");
			data = nullptr;

			// Get a stream Object* for reading and writing.
			NetworkStream^ stream = client->GetStream();
			Int32 i;

			// Loop to receive all the data sent by the client.
			while (i = stream->Read(bytes, 0, bytes->Length))
			{
				data = Text::Encoding::Unicode->GetString(bytes, 0, i);
				Console::WriteLine("Received: {0}", data);

				// Process the data sent by the client.
				data = data->ToUpper();
				array<Byte>^ message = Text::Encoding::Unicode->GetBytes(data);

				// Send back a response.
				stream->Write(message, 0, message->Length);
				Console::WriteLine("Sent: {0}", data);
			}
			// Shutdown and end connection
			client->Close();
		}
	}
	catch (SocketException ^ e)
	{
		Console::WriteLine("SocketException: {0}", e);
	}
}
