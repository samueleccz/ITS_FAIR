var boolResize=false; //Gloabal Variable for terminalResize()
var boolIconing=false; //Global Variable for terminalIcon()
var boolClosing=false; //Global Variable for terminalClose() 
var boolSecondTime=false;

//SERP API
//https://serpapi.com/search.json?engine=google&q=" + searchVariable
//Project Incomplete

//OPENWEATHER API
//https://api.openweathermap.org/data/2.5/weather?q=CITYNAME,CA&appid=apiKey
//https://api.openweathermap.org/data/2.5/weather?q=Palagonia&appid=fc44c5ca70814db66355396e6f65ad71

//OPENWEATHER COORDINATE 
//https://api.openweathermap.org/data/2.5/weather?q=CITYNAME,CA&appid=apiKey
//https://api.openweathermap.org/data/2.5/weather?q=Palagonia&appid=fc44c5ca70814db66355396e6f65ad71

//JOJO STANDS API
//https://stand-by-me.herokuapp.com/api/v1/stands/query/query?name=StandName
//https://stand-by-me.herokuapp.com/api/v1/stands/query/query?name=Weather Report

function terminalClose(){ //Function Closing of Terminal
    const terminal = document.getElementById("idTerminal");
    
    boolClosing = true;
    terminal.remove();
    console.log("terminal closed");
};

function terminalResize(){ //Function Resize of Console
  const terminal = document.getElementById("idTerminal");
  const frame = document.getElementById("idFrame");  

  frame.style.left = "0px";
  frame.style.top = "0px";

  let screenHeight = window.screen.height;
  let screenWidth = window.screen.width;
  
  if(boolResize==false){ //Boolean Control for Upscaling
    terminal.style.height = screenHeight-118 + "px";  
    terminal.style.width = screenWidth-50+ "px";
    boolResize = true;
    console.log("terminal upscaled");
  }
  else{ //Boolean Control for Downscaling
    terminal.style.height = "250px";  
    terminal.style.width = "500px";
    boolResize = false;
    console.log("terminal downscaled");
  }
};

function terminalIcon(){ //Boolean Control for Console Standby
  const terminal = document.getElementById("idTerminal");
  terminal.style.display = "none";
  boolIconing = true;
  console.log("terminal iconed");
};

function showTerminal() {
  boolSecondTime = true;
  if(boolIconing==true){
    const terminal = document.getElementById("idTerminal");
    terminal.style.display = "block";
    boolIconing = false;
    console.log("terminal deiconed");
  }
  
  if(boolClosing==true){
    const terminalVariable = document.createElement("div");
    terminalVariable.classList.add("terminal");
    terminalVariable.id = "idTerminal";
    document.body.querySelector(".frame").appendChild(terminalVariable);

    const headerVariable = document.createElement("div");
    headerVariable.classList.add("header");
    terminalVariable.appendChild(headerVariable);

    const iconVariable = document.createElement("button");
    iconVariable.classList.add("icon");
    iconVariable.onclick = terminalIcon;
    iconVariable.innerHTML = "-";
    iconVariable.style.margin = "0px 4px 0px 0px";
    headerVariable.appendChild(iconVariable);

    const resizeVariable = document.createElement("button");
    resizeVariable.classList.add("resize");
    resizeVariable.onclick = terminalResize;
    resizeVariable.innerHTML = "||";
    resizeVariable.style.margin = "0px 4px 0px 0px";
    headerVariable.appendChild(resizeVariable);

    const closeVariable = document.createElement("button");
    closeVariable.classList.add("close");
    closeVariable.onclick = terminalClose;
    closeVariable.innerHTML = "X";
    closeVariable.style.margin = "0px 4px 0px 0px";
    headerVariable.appendChild(closeVariable);
    
    const terminalNameVariable = document.createElement("small");
    terminalNameVariable.classList.add("nameTerminal");
    terminalNameVariable.innerHTML = "samueleccz's Terminal";
    headerVariable.appendChild(terminalNameVariable);
    
    const textAreaVariable = document.createElement("div");
    textAreaVariable.classList.add("text");
    textAreaVariable.id = "idText";
    terminalVariable.appendChild(textAreaVariable);

    const beforeVariable = document.createElement("span");
    beforeVariable.classList.add("before");
    beforeVariable.innerHTML = "C:/Users/scucu>";
    textAreaVariable.appendChild(beforeVariable);

    const inputVariable = document.createElement("span");
    inputVariable.classList.add("input");
    inputVariable.id = "idInput";
    inputVariable.contentEditable = true;
    inputVariable.autofocus = true;
    textAreaVariable.appendChild(inputVariable);
    inputVariable.addEventListener("keydown", function (e) {
      if (e.key === "Enter") {
        changeRow();
      }
  });

    boolClosing = false;
  }
};


document.addEventListener("DOMContentLoaded", function(){
  let t = document.getElementById("idInput");

  if(t){
    t.addEventListener("keydown", function(e){
      if(e.key === "Enter"){
        //alert("premuto enter");
        changeRow();
        e.preventDefault();
      }
    })
  }
});

function sum(n1, n2){
  return n1 + n2;
};

function changeRow(){
    let primeText = document.getElementById("idInput");
    if(primeText.innerHTML == ""){
    boolSecondTime = true;
    let terminalUpgrade = document.getElementById("idText");

    primeText.contentEditable = false;
    primeText.id = "idOld";

    const br = document.createElement("br");
    terminalUpgrade.appendChild(br);

    const row = document.createElement("span");
    row.classList.add("before");
    row.innerHTML = "C:/Users/scucu>";
    terminalUpgrade.appendChild(row);

    const inputRow = document.createElement("span");
    inputRow.classList.add("input");
    inputRow.id = "idInput";
    inputRow.contentEditable = true;
    inputRow.autofocus = true;
    terminalUpgrade.appendChild(inputRow);
    inputRow.addEventListener("keydown", function (e) {
      if (e.key === "Enter") {
          changeRow();
      }
  });
  
    console.log("created empty");
    }
    else if(primeText.innerHTML == "/hello"){
      let terminalUpgrade = document.getElementById("idText");
      boolSecondTime = true;

      primeText.contentEditable = false;
      primeText.id = "idOld";

      const br = document.createElement("br");
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = " hi boss, how can i /help you?";
      terminalUpgrade.appendChild(resultRow);

      const br1 = document.createElement("br");
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
    }
    else if(primeText.innerHTML == "/doom"){
      let terminalUpgrade = document.getElementById("idText");
      boolSecondTime = true;

      primeText.contentEditable = false;
      primeText.id = "idOld";

      const br = document.createElement("br");
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = "'Against all the evil that Hell can conjure, all the wickedness that mankind can produce, we will send unto them... only you. Rip and tear, until it is done'";
      terminalUpgrade.appendChild(resultRow);

      const br2 = document.createElement("br");
      terminalUpgrade.appendChild(br2);

      const imageDoom = document.createElement("img");
      imageDoom.src = "https://th.bing.com/th/id/OIP.lTwHB04aEfYC1cUiApwm4gHaHa?rs=1&pid=ImgDetMain";
      imageDoom.style.height = "50px";
      imageDoom.style.width = "50px";
      imageDoom.style.align = "center";
      terminalUpgrade.appendChild(imageDoom);

      const br1 = document.createElement("br");
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.focus();
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
    }

    else if(primeText.innerHTML == "/doomITA"){
      let terminalUpgrade = document.getElementById("idText");
      boolSecondTime = true;

      primeText.contentEditable = false;
      primeText.id = "idOld";

      const br = document.createElement("br");
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = "'Contro tutto il male che l'inferno può evocare, contro tutta la malvagità che l'umanità può produrre, noi manderemo... Soltanto te. Strappa e squarta, finché non sarà finita'";
      terminalUpgrade.appendChild(resultRow);

      const br2 = document.createElement("br");
      terminalUpgrade.appendChild(br2);

      const imageDoom = document.createElement("img");
      imageDoom.src = "https://th.bing.com/th/id/OIP.lTwHB04aEfYC1cUiApwm4gHaHa?rs=1&pid=ImgDetMain";
      imageDoom.style.height = "50px";
      imageDoom.style.width = "50px";
      imageDoom.style.align = "center";
      terminalUpgrade.appendChild(imageDoom);

      const br1 = document.createElement("br");
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
    }

    else if(primeText.innerHTML == "/clear"){
      const terminalVariable = document.getElementById("idTerminal");
      boolSecondTime = true;
      const terminal = document.getElementById("idText");
      terminal.remove();
      
      console.log("terminal cleared");

      const textAreaVariable = document.createElement("div");
      textAreaVariable.classList.add("text");
      textAreaVariable.id = "idText";
      terminalVariable.appendChild(textAreaVariable);

      const beforeVariable = document.createElement("span");
      beforeVariable.classList.add("before");
      beforeVariable.innerHTML = "C:/Users/scucu>";
      textAreaVariable.appendChild(beforeVariable);

      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      textAreaVariable.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
    }
    else if(primeText.innerHTML == "/help"){
      let terminalUpgrade = document.getElementById("idText");
      boolSecondTime = true;
      let helpString = "Command List: </br> <span> - /hello : Say hello to the console; </span> </br> <span> - /doom : Console will say the DOOM intro phrase; </span> </br> <span> - /doomITA : Console will say the DOOM intro phrase in italian </span> </br> <span> - /clear : Clear the console from old command; </span> </br> <span> - /sum [n1] [n2]: Execute the sum of n1 and n2; </span> </br> <span> - /date : Show the current Date; </span>  </br> <span> - /weatherReport [s]: Generate the weatherReport of the s city; </span> </br> - /coordinate [s]: Generate the Coordinate of the s city; </span> </br> - /JOJOstand [s]: Tells you the abilities of the s JOJO stand; </span>";
          primeText.contentEditable = false;
          primeText.id = "idOld";
          //console.log(helpString);
  
          const br = document.createElement("br");
          terminalUpgrade.appendChild(br);
  
          const resultRow = document.createElement("span");
          resultRow.classList.add("result");
          resultRow.id = "idResult";
          resultRow.innerHTML = helpString;
          terminalUpgrade.appendChild(resultRow);
  
          const br1 = document.createElement("br");
          terminalUpgrade.appendChild(br1);
  
          const row = document.createElement("span");
          row.classList.add("before");
          row.innerHTML = "C:/Users/scucu>";
          terminalUpgrade.appendChild(row);
  
          const inputRow = document.createElement("span");
          inputRow.classList.add("input");
          inputRow.id = "idInput";
          inputRow.contentEditable = true;
          inputRow.autofocus = true;
          terminalUpgrade.appendChild(inputRow);
          inputRow.addEventListener("keydown", function (e) {
            if (e.key === "Enter") {
              changeRow();
            }
          });
    }
    else if(primeText.innerHTML.substring(0,4) === "/sum" ){        
      boolSecondTime = true;
      let firstSpace = primeText.innerHTML.indexOf(' ');
      let secondSpace = primeText.innerHTML.substring(firstSpace+1, 200).indexOf(' ');

      let n1 = primeText.innerHTML.substring(firstSpace, secondSpace+(firstSpace+1));
      let n2 = primeText.innerHTML.substring(secondSpace+firstSpace+1);
      let numerator1 = parseFloat(n1);
      let numerator2 = parseFloat(n2);
      let result = sum(numerator1,numerator2);
      
      let terminalUpgrade = document.getElementById("idText");

      primeText.contentEditable = false;
      primeText.id = "idOld";

      const br = document.createElement("br");
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = " Your requested sum is: " + numerator1 + "+" + numerator2 + "=" + result;
      terminalUpgrade.appendChild(resultRow);

      const br1 = document.createElement("br");
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
    }//const d = new Date()
    else if(primeText.innerHTML.substring(0,7) === "/date"){   
      boolSecondTime = true;     
      let terminalUpgrade = document.getElementById("idText");
      const dateString = new Date()
      primeText.contentEditable = false;
      primeText.id = "idOld";

      const br = document.createElement("br");
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = dateString;
      terminalUpgrade.appendChild(resultRow);

      const br1 = document.createElement("br");
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
    }
    else if(primeText.innerHTML.substring(0,14) === "/weatherReport"){        
      researchString = primeText.innerHTML + '|';;
      let bar = researchString.indexOf('|');
      let stringSearch = researchString.substring(14,bar);

      let apiUrl = "https://api.openweathermap.org/data/2.5/weather?q="+stringSearch+"&appid=fc44c5ca70814db66355396e6f65ad71";
      let resultApi;
      
      fetch(apiUrl)
      .then(response => response.json())
      .then(data => {
         resultApi = data;

         let temperature = resultApi.main.temp-273;
         let terminalUpgrade = document.getElementById("idText");
         let temperatureParse = parseInt(temperature);
         let weatherLike = resultApi.weather[0].main;

      primeText.contentEditable = false;
      primeText.id = "idOld";

      if(boolSecondTime===true){
        const inutilBr = document.querySelector("#idOld>br");
        inutilBr.remove();
        const inutilBr2 = document.querySelector("#idOld>br");
        inutilBr2.remove();
      }
      boolSecondTime = true;
      
      const br = document.createElement("br");
      br.id = "primo";
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = "In the city of " + stringSearch + " there are " + temperatureParse + "° Degree and the weather is " + weatherLike;
      terminalUpgrade.appendChild(resultRow);

      const br1 = document.createElement("br");
      br1.id = "secondo";
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
      })
      .catch(error => {
        console.log(error);
        let terminalUpgrade = document.getElementById("idText");
        primeText.contentEditable = false;
        primeText.id = "idOld";

        if(boolSecondTime===true){
          const inutilBr = document.querySelector("#idOld>br");
          console.log(inutilBr);
          inutilBr.remove();
  
          const inutilBr2 = document.querySelector("#idOld>br");
          inutilBr2.remove();
        }
        boolSecondTime = true;
        
        const br = document.createElement("br");
        br.id = "primo";
        terminalUpgrade.appendChild(br);
  
        const resultRow = document.createElement("span");
        resultRow.classList.add("result");
        resultRow.id = "idResult";
        resultRow.innerHTML = "Request Failed, try to insert a correct cityName or cityName,country. EX. New York or Catania, IT";
        terminalUpgrade.appendChild(resultRow);
  
        const br1 = document.createElement("br");
        br1.id = "secondo/";
        terminalUpgrade.appendChild(br1);
  
        const row = document.createElement("span");
        row.classList.add("before");
        row.innerHTML = "C:/Users/scucu>";
        terminalUpgrade.appendChild(row);
    
        const inputRow = document.createElement("span");
        inputRow.classList.add("input");
        inputRow.id = "idInput";
        inputRow.contentEditable = true;
        inputRow.autofocus = true;
        terminalUpgrade.appendChild(inputRow);
        inputRow.addEventListener("keydown", function (e) {
          if (e.key === "Enter") {
              changeRow();
          }
      });
      })
    }
    else if(primeText.innerHTML.substring(0,11) === "/coordinate"){        
           researchString = primeText.innerHTML + '|';;
           let bar = researchString.indexOf('|');
           let stringSearch = researchString.substring(11,bar);
     
           let apiUrl = "https://api.openweathermap.org/data/2.5/weather?q="+stringSearch+"&appid=fc44c5ca70814db66355396e6f65ad71";
           let resultApi;
           
           fetch(apiUrl)
           .then(response => response.json())
           .then(data => {
              resultApi = data;
     
              let terminalUpgrade = document.getElementById("idText");
              let coordLon = resultApi.coord.lon;
              let coordLat = resultApi.coord.lat;
     
              //console.log(weatherLike);
           primeText.contentEditable = false;
           primeText.id = "idOld";

          if(boolSecondTime===true){
            const inutilBr = document.querySelector("#idOld>br");
            console.log(inutilBr);
            inutilBr.remove();
    
            const inutilBr2 = document.querySelector("#idOld>br");
            inutilBr2.remove();
          }
          boolSecondTime = true;
     
           const br = document.createElement("br");
           br.id = "primo";
           terminalUpgrade.appendChild(br);
     
           const resultRow = document.createElement("span");
           resultRow.classList.add("result");
           resultRow.id = "idResult";
           resultRow.innerHTML = "The coordinates of " + stringSearch + " are: <br/> latitude= " + coordLat + " , longitude=" + coordLon;
           terminalUpgrade.appendChild(resultRow);
     
           const br1 = document.createElement("br");
           br1.id = "secondo";
           terminalUpgrade.appendChild(br1);
     
           const row = document.createElement("span");
           row.classList.add("before");
           row.innerHTML = "C:/Users/scucu>";
           terminalUpgrade.appendChild(row);
       
           const inputRow = document.createElement("span");
           inputRow.classList.add("input");
           inputRow.id = "idInput";
           inputRow.contentEditable = true;
           inputRow.autofocus = true;
           terminalUpgrade.appendChild(inputRow);
           inputRow.addEventListener("keydown", function (e) {
             if (e.key === "Enter") {
                 changeRow();
             }
         });
           })
           .catch(error => {
             console.log(error);
             let terminalUpgrade = document.getElementById("idText");
             primeText.contentEditable = false;
             primeText.id = "idOld";

            if(boolSecondTime===true){
              const inutilBr = document.querySelector("#idOld>br");
              console.log(inutilBr);
              inutilBr.remove();
      
              const inutilBr2 = document.querySelector("#idOld>br");
              inutilBr2.remove();
            }
            boolSecondTime = true;
       
             const br = document.createElement("br");
             br.id = "primo";
             terminalUpgrade.appendChild(br);
       
             const resultRow = document.createElement("span");
             resultRow.classList.add("result");
             resultRow.id = "idResult";
             resultRow.innerHTML = "Request Failed, try to insert a correct cityName or cityName,country. EX. New York or Catania, IT";
             terminalUpgrade.appendChild(resultRow);
       
             const br1 = document.createElement("br");
             br1.id = "secondo/";
             terminalUpgrade.appendChild(br1);
       
             const row = document.createElement("span");
             row.classList.add("before");
             row.innerHTML = "C:/Users/scucu>";
             terminalUpgrade.appendChild(row);
         
             const inputRow = document.createElement("span");
             inputRow.classList.add("input");
             inputRow.id = "idInput";
             inputRow.contentEditable = true;
             inputRow.autofocus = true;
             terminalUpgrade.appendChild(inputRow);
             inputRow.addEventListener("keydown", function (e) {
               if (e.key === "Enter") {
                   changeRow();
               }
           });
           })
    }
    else if(primeText.innerHTML.substring(0,10) === "/JOJOstand"){        
      researchString = primeText.innerHTML + '|';;
      let bar = researchString.indexOf('|');
      let JojoStand = researchString.substring(11,bar);

      let apiUrl = "https://stand-by-me.herokuapp.com/api/v1/stands/query/query?name="+JojoStand;
      let resultApi;
      
      fetch(apiUrl)
      .then(response => response.json())
      .then(data => {
         console.log(data);
         resultApi = data;
         const name = data[0].name;
         console.log(name);

         let terminalUpgrade = document.getElementById("idText");

         //console.log(weatherLike);
      primeText.contentEditable = false;
      primeText.id = "idOld";

     if(boolSecondTime===true){
       const inutilBr = document.querySelector("#idOld>br");
       console.log(inutilBr);
       inutilBr.remove();

       const inutilBr2 = document.querySelector("#idOld>br");
       inutilBr2.remove();
     }
     boolSecondTime = true;

      const br = document.createElement("br");
      br.id = "primo";
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = "Your requested JOJO stand is: <br> Name: " + resultApi[0].name + "<br> Abilities: " + resultApi[0].abilities + ' </br> <img style="width: 200px; height:200px;" src="https://jojos-bizarre-api.netlify.app/assets/'+resultApi[0].image+'">';
      console.log(resultApi[0].name);
      terminalUpgrade.appendChild(resultRow);

      const br1 = document.createElement("br");
      br1.id = "secondo";
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);
  
      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
            changeRow();
        }
    });
      })
      .catch(error => {
        console.log(error);
        let terminalUpgrade = document.getElementById("idText");
        primeText.contentEditable = false;
        primeText.id = "idOld";

       if(boolSecondTime===true){
         const inutilBr = document.querySelector("#idOld>br");
         console.log(inutilBr);
         inutilBr.remove();
 
         const inutilBr2 = document.querySelector("#idOld>br");
         inutilBr2.remove();
       }
       boolSecondTime = true;
  
        const br = document.createElement("br");
        br.id = "primo";
        terminalUpgrade.appendChild(br);
  
        const resultRow = document.createElement("span");
        resultRow.classList.add("result");
        resultRow.id = "idResult";
        resultRow.innerHTML = "Request Failed, try to insert a correct JOJO stand Name. EX. Weather Report";
        terminalUpgrade.appendChild(resultRow);
  
        const br1 = document.createElement("br");
        br1.id = "secondo/";
        terminalUpgrade.appendChild(br1);
  
        const row = document.createElement("span");
        row.classList.add("before");
        row.innerHTML = "C:/Users/scucu>";
        terminalUpgrade.appendChild(row);
    
        const inputRow = document.createElement("span");
        inputRow.classList.add("input");
        inputRow.id = "idInput";
        inputRow.contentEditable = true;
        inputRow.autofocus = true;
        terminalUpgrade.appendChild(inputRow);
        inputRow.addEventListener("keydown", function (e) {
          if (e.key === "Enter") {
              changeRow();
          }
      });
      })
}
    else if(primeText.innerHTML != null ){
      let terminalUpgrade = document.getElementById("idText");
      boolSecondTime = true;

      primeText.contentEditable = false;
      primeText.id = "idOld";

      const br = document.createElement("br");
      terminalUpgrade.appendChild(br);

      const resultRow = document.createElement("span");
      resultRow.classList.add("result");
      resultRow.id = "idResult";
      resultRow.innerHTML = " Wrong command, type /help for the command list; Comando errato, digita /help per la lista dei comandi";
      terminalUpgrade.appendChild(resultRow);

      const br1 = document.createElement("br");
      terminalUpgrade.appendChild(br1);

      const row = document.createElement("span");
      row.classList.add("before");
      row.innerHTML = "C:/Users/scucu>";
      terminalUpgrade.appendChild(row);

      const inputRow = document.createElement("span");
      inputRow.classList.add("input");
      inputRow.id = "idInput";
      inputRow.contentEditable = true;
      inputRow.autofocus = true;
      terminalUpgrade.appendChild(inputRow);
      inputRow.addEventListener("keydown", function (e) {
        if (e.key === "Enter") {
          changeRow();
        }
      });
    }
};