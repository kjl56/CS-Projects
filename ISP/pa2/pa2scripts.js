function displayDate () {
  var d = new Date();
  var time = [d.getHours(), d.getMinutes(), d.getSeconds()].join(':'); 
  var date = [d.getMonth(), d.getDate(), d.getFullYear()].join('/');
  document.getElementById("Date").innerHTML = [date, time].join(' ');
}
setInterval(displayDate, 1000);

function computeFactorial(num) {
  var result = 1;
  for (var i = num; i != 1; i--) {
    result *= i;
  }
  return result;
}

function checkValue(input) {
  //if input is not a number, alert user
  if (isNaN(input)) {
      alert("must input a number");
  } else { 
    //if number is negative, alert user
    if (input <= 0) {
      alert("number must be positive");
    } else {
      var factorial = computeFactorial(input);
      document.getElementById("factorial").innerHTML = "the number's factorial is: " + factorial;
    }
  } 
}

function checkEmailStatic(email) {
  //first checks string has no invalid characters/ combinations
  var re = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;
  if(re.test(email)) {
    //divides string into three parts
    var atPos = email.indexOf("@");
    var dotPos = email.indexOf(".");
    var emailSub1 = email.substring(0, atPos);
    var emailSub2 = email.substring(atPos+1, dotPos);
    var emailSub3 = email.substring(dotPos+1);
    //checks parts 1 and 2 only have characters and numbers
    if (!/[^a-zA-Z0-9]/.test(emailSub1) && !/[^a-zA-Z0-9]/.test(emailSub2)) {
      //checks part 3 only has a max of 3 letters
      if (emailSub3.length <= 3) {
        document.getElementById("firstEmailResult").innerHTML = email + " is a valid email";
      } else {
        document.getElementById("firstEmailResult").innerHTML = "not a valid email";
      }
    } else {
      document.getElementById("firstEmailResult").innerHTML = "not a valid email";
    }
  } else {
    document.getElementById("firstEmailResult").innerHTML = "not a valid email";
  }
}

function checkEmailDynamic(email) {
  //first checks string has no invalid characters/ combinations
  var re = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;
  if(re.test(email)) {
    //divides string into three parts
    var atPos = email.indexOf("@");
    var dotPos = email.indexOf(".");
    var emailSub1 = email.substring(0, atPos);
    var emailSub2 = email.substring(atPos+1, dotPos);
    var emailSub3 = email.substring(dotPos+1);
    //checks parts 1 and 2 only have characters and numbers
    if (!/[^a-zA-Z0-9]/.test(emailSub1) && !/[^a-zA-Z0-9]/.test(emailSub2)) {
      //checks part 3 only has a max of 3 letters
      if (emailSub3.length <= 3) {
        document.getElementById("secondEmailResult").innerHTML = email + " is a valid email";
      } else {
        document.getElementById("secondEmailResult").innerHTML = "not a valid email";
      }
    } else {
      document.getElementById("secondEmailResult").innerHTML = "not a valid email";
    }
  } else {
    document.getElementById("secondEmailResult").innerHTML = "not a valid email";
  }
}

function moveImage(event) {
  event = event || window.event;
  var clickX = event.pageX;
  var clickY = event.pageY;
  
  var pic = document.getElementById("picture");

  //start and end position of picture
  var picStartX = parseInt(pic.style.left, 10);
  var picStartY = parseInt(pic.style.top, 10);
  var picEndX = parseInt(clickX, 10) - 150;
  var picEndY = parseInt(clickY, 10) - 100;

  //divide travel distance between start and end position over 100 frames
  var frames = 100; 
  var picXInterval = (picEndX - picStartX) / frames;
  var picYInterval = (picEndY - picStartY) / frames;
  
  //display a frame every 20 milliseconds
  var animate = setInterval(frame, 20);
  function frame() {
    var tempX = picStartX;
    var tempY = picStartY;
    if (frames == 0) {
      clearInterval(animate);
    } else {
      frames--;
      tempX += picXInterval;
      tempY += picYInterval;
      pic.style.left = tempX + "px";
      pic.style.top = tempY + "px";
    }
  }

  //pic.style.left = clickX - 150 + "px";
  //pic.style.top = clickY -100 + "px";
}

var body = document.getElementById("body");
body.addEventListener("load", displayDate);
body.addEventListener("click", moveImage);
