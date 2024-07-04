let nicknameUser = "";
let socket;

const loginView = document.querySelector("#loginform");
const chatView = document.querySelector("#chatview");
const nicknameInput = document.querySelector("#nicknameInput");
const btnLogin = document.querySelector("#btn-login");
const listUsersDom = document.querySelector("#listausers");

const containerMessaggi = document.querySelector("#containerMessaggi");
const inputMessage = document.querySelector("#inputMessage");
const btnSend = document.querySelector("#send_btn");


const popolateUsers = (list) => {
    listUsersDom.innerHTML = "";
    for(user of list){

        const htmlUser = '<li data-nickname="'+user.nickname+'">\
                                <div class="d-flex bd-highlight">\
                                    <div class="img_cont">\
                                        <img src="https://ui-avatars.com/api/?name='+user.nickname+'" class="rounded-circle user_img" />\
                                        <span class="online_icon online"></span>\
                                    </div>\
                                    <div class="user_info">\
                                        <span>'+user.nickname+'</span>\
                                    </div>\
                                </div>\
                            </li>';
        listUsersDom.innerHTML+=htmlUser;

    }
};

const insertUser = (nickname) => {
        const htmlUser = '<li data-nickname="'+nickname+'">\
                                <div class="d-flex bd-highlight">\
                                    <div class="img_cont">\
                                        <img src="https://ui-avatars.com/api/?name='+nickname+'" class="rounded-circle user_img" />\
                                        <span class="online_icon online"></span>\
                                    </div>\
                                    <div class="user_info">\
                                        <span>'+nickname+'</span>\
                                    </div>\
                                </div>\
                            </li>';
        listUsersDom.innerHTML+=htmlUser;
};

const removeUser = (nickname) => {
    listUsersDom.querySelector("li[data-nickname="+nickname+"]").remove();
}


const sendMessage = () => {
    const message = inputMessage.value;
    inputMessage.value = "";
    socket.emit("sendMessage", message);
    const ora = new Date();
    const stringaData = ora.getHours()+":"+ora.getMinutes();

    const htmlElement = '<div class="d-flex justify-content-end mb-4">\
                            <div class="msg_cotainer_send">\
                                '+message+'\
                                <span class="msg_time_send">'+stringaData+'</span>\
                            </div>\
                            <div class="img_cont_msg">\
                                <img src="https://ui-avatars.com/api/?name='+nicknameUser+'" class="rounded-circle user_img_msg" />\
                            </div>\
                        </div>';
    containerMessaggi.innerHTML+= htmlElement;


};

const insertMessage = (nickname, message) => {
    const ora = new Date();
    const stringaData = ora.getHours()+":"+ora.getMinutes();

    const htmlElement = ' <div class="d-flex justify-content-start mb-4">\
                            <div class="img_cont_msg">\
                                <img src="https://ui-avatars.com/api/?name='+nickname+'"                                    class="rounded-circle user_img_msg" />\
                            </div>\
                            <div class="msg_cotainer">\
                                <div class="text-muted h6">'+nickname+'</div>\
                                '+message+'\
                                <span class="msg_time mt-4">'+stringaData+'</span>\
                            </div>\
                        </div>';
    containerMessaggi.innerHTML+= htmlElement;


};

btnSend.addEventListener("click", () => {
    sendMessage();
});

btnLogin.addEventListener("click", () => {
    nicknameUser =  nicknameInput.value;

    socket = io();

    socket.on("connect", async () => {
        console.log("Connesso");
        containerMessaggi.innerHTML = "";
        loginView.classList = "container-fluid h-100 hidden";
        chatView.classList = "container-fluid h-100";
        socket.emit("userLogged", nicknameUser);
        const resp = await fetch("/api/users");
        const listUsers = await resp.json();
        popolateUsers(listUsers);
    });

    socket.on("disconnect", () => {
        console.log("Disconnesso");
        loginView.classList = "container-fluid h-100";
        chatView.classList = "container-fluid h-100 hidden"
    });

    socket.on("userLogged", (nicknameLogged) => {
        console.log("Tizio si è collegato", nicknameLogged)
        insertUser(nicknameLogged);
    });

    socket.on("userDisconnected", (nicknameSlogged) => {
        console.log("Tizio si è disconnesso", nicknameSlogged)
        removeUser(nicknameSlogged);
    });

    socket.on("newMessage", (nicknameSender, message) => {
        insertMessage(nicknameSender, message);
    });
});