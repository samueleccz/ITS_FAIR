/*CREATE TERMINAL ALTERNATIVE*/


createTerminal = () =>{
  console.log("ok");
  const mainContainer = document.querySelector(".frame");

  mainContainer.innerHTML='<div class="terminal" id="idTerminal">\
                              <div class="header">\
                                  <button class="icon" onclick="terminalIcon()"> - </button>\
                                  <button class="resize" onclick="terminalResize()"> || </button>\
                                  <button class="close" onclick="terminalClose()"> X </button>\
                                  <small class="nameTerminal"> samuelecczs Terminal </small>\
                              </div>\
                              <div class="text">\
                                  <span class="before">C:/Users/scucu></span>\
                                  <span class="input" id="idInput" contenteditable="true" autofocus></span>\
                              </div>'

    console.log("opened");
};