#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

  <title>Document</title>
  <style>
    #mycolor{
      border: 1px solid black;
      width: 100px;
      height: 100px;
      background-color: transparent;
    }

    button{
      height: 50px;
      width: 100px;
      font-size: 20px;
      font-family: sans-serif;
      margin-top: 20px;
      background-color: transparent;
      border: 1px solid black;
    }

    div{
      display: flex;
      flex-flow: column nowrap;
      justify-content: center;
      align-items: center;
      background-color: transparent;
      width: auto;

      padding: 20px;
      margin: 200px 20px;
      border-radius: 40px;
      border: 1px solid black;
    }
  </style>
</head>
<body>
  <div>
    <input id = "mycolor" type="color" value = "#FFFFFF">
    <button id = "mybutton">SEND</button>
  </div>
  <script>
    const picker = document.querySelector('#mycolor');
    const button = document.querySelector('#mybutton');
    var data = {
      r: 255, g: 255, b: 255
    };

    button.addEventListener("click", (e)=>{
      fetch('/data', {
        method: 'POST', 
        mode: 'cors',
        headers:{
          "Content-Type": "application/x-www-form-urlencoded"
        },
        body: `R=${data.r}&G=${data.g}&B=${data.b}`,
      })
        .then(res=>console.log(res))
        .catch(err=>console.log(err));
    });

    picker.addEventListener("change", (e) => {
      const color = e.target.value;
      data = {
        r: parseInt(color.substr(1,2), 16),
        g: parseInt(color.substr(3,2), 16),
        b: parseInt(color.substr(5,2), 16)
      }
    });
  </script>
</body>
</html>
)rawliteral";