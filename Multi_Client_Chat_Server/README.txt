

		---------Multi Client Chat server---------

This is an implementation of a client-server chat application using TCP sockets. There will be a single server and multiple clients communicating with the server. The server process  can  handle  at  most  5  concurrent  connections.


			Functionalities implemented :-

1./active : To display all the available active clients that are connected to theserver.2./send <dest client id> <Message> : To send message to the client corresponding to its unique id.3./broadcast <Message> : Message should be broadcasted to all the activeclients.4./makegroup <client id1> <client id2> ...<client idn> : A group with unique id will be made including all the mentioned clients along with the adminclient.5./sendgroup  <group  id>  <Message>:  The  sender  should  be  in  the  group  to  transfer the  message  to  all  his  peers  of  that  group.  The  message  should  be  send  to  all  the peers along with group info.6./activegroups : To display all the groups that are currently active on server and the sender is a part of.


			How to run code :-

1. Open terminal and run "make"
2. Run "./s"
3. Open new terminal and run "./c1"
4. Repeat step 3 for every new client
