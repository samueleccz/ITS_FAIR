const express = require("express");

const serverExpress = express();
const serverHTTP = require('http').Server(serverExpress);
const serverSocketIO = require('socket.io')(serverHTTP);

const listUsers = [];

serverExpress.use(express.static("./www"));


serverExpress.get("/api/users", (req, resp) => {
    resp.json(listUsers);
});

//gestiremo le websocket 

serverSocketIO.on("connection", (socketClient) => {
    console.log("Client Collegato");

    socketClient.on("disconnect", () => {
        console.log("Il client si è disconnesso");
        for(const index in listUsers){
            if(listUsers[index].id == socketClient.id){
                listUsers.splice(index, 1);
                break;
            }
        }
        if(socketClient.nickname){
            serverSocketIO.sockets.emit("userDisconnected", socketClient.nickname);
        }
    });

    socketClient.on("userLogged", (nickname) => {

        socketClient["nickname"] = nickname;
        socketClient.broadcast.emit("userLogged", nickname);
        const userObject = {
            id : socketClient.id,
            nickname : nickname
        };
        listUsers.push(userObject);
    });

    socketClient.on("sendMessage", (messaggio) => {
        socketClient.broadcast.emit("newMessage", socketClient.nickname, messaggio);
    });
});

//mi metto in ascolto sulla porta X
serverHTTP.listen(8080);