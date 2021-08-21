#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title>test</title>
    <style>
      div{
        border: 1px solid crimson;
        display: flex;
        flex-flow: row nowrap;
        justify-content: center;
        align-items: center;
        color: crimson;
        font-size: 40px;
        font-family: sans-serif;
      }
    </style>
  </head>
  <body>
    <div onclick="send_to_esp();">
			<p>Hello User</p>
    </div>
  </body>

	<script>
		function send_to_esp(){
			fetch('./data', {
				method: "POST", 
				mode: 'cors',
			}).then(res=>res.text()).then(res=>console.log(res));
		}
	</script>
</html>
)rawliteral";