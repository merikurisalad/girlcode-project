function changeDressImage() {
  if (document.getElementById("model").src.match("modeldress.png")) {
    document.getElementById("model").src = "modelresized.png";
  } else {
    document.getElementById("model").src = "modeldress.png";
  }
}

function changeSkirtImage() {
 if (document.getElementById("model").src.match("modelshirt.png")) {
    document.getElementById("model").src = "modelfull.png";
  } else if (document.getElementById("model").src.match("modelfull.png")) {
   document.getElementById("model").src = "modelshirt.png";
 } else if (document.getElementById("model").src.match("modelskirt.png")) {
   document.getElementById("model").src = "modelresized.png";
 } else {
   document.getElementById("model").src = "modelskirt.png";
 }
}

function changeShirtImage() {
  if (document.getElementById("model").src.match("modelfull.png")) {
    document.getElementById("model").src = "modelskirt.png";
  } else if (document.getElementById("model").src.match("modelskirt.png")) {
    document.getElementById("model").src = "modelfull.png";
  } else if (document.getElementById("model").src.match("modelshirt.png")) {
    document.getElementById("model").src = "modelresized.png";
  } else {
    document.getElementById("model").src = "modelshirt.png";
  }
}
