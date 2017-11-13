//Adjust Speed of Background Video
//var vid = document.getElementById("video-elem");
//vid.playbackRate = 0.75;

//Video Stream (getUserMedia)
var video = document.querySelector("#videoElement");

navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia || navigator.oGetUserMedia;
 
if (navigator.getUserMedia) {       
    navigator.getUserMedia({video: true}, handleVideo, videoError);
}
 
function handleVideo(stream) {
    video.src = window.URL.createObjectURL(stream);
}

function videoError(e) {
    // do something
}
