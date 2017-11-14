// The code that runs after emscripten/db is fully loaded.
let main = function() {
    Module.clearTemporaryStorage();  // Clear temporary storage on page load.
    Module.addCustomer_init();

    // Ran when the Take Picture button is clicked.
    document.getElementById("tpButton").onclick = function(){
        let canvas = document.createElement('canvas');
        let ctx = canvas.getContext('2d');

        //draw image to canvas. scale to target dimensions
        ctx.drawImage(video, 0, 0, canvas.width, canvas.height);

        //convert to desired file format
        let dataURI = canvas.toDataURL('image/png').replace('data:image/png;base64,','');

        // Crop the face and save it to temporary storage.
        let success = Module.addCustomer_saveFaceInTemporaryStorage(dataURI);
        if (!success) {
            return;
        }
        
        // Display the updated faces.
        let preview = document.getElementById("images");
        preview.style.display = "flex";
        let newImage = document.createElement("img");
        newImage.src = "data:image/png;base64," + Module.addCustomer_mostRecentDetectedFace();
        newImage.classList.add("croppedImage");
        preview.appendChild(newImage);
    };

    // Ran when the "save" button is clicked.
    document.getElementById("save-button").onclick = function() {
        let studentId = window.parseInt(document.getElementById("studentId-form").value);
        if (!studentId) {
            alert("Invalid studentId");
        }

        Module.addCustomer_clean();
        Module.persist().then(() => {
            let nextURL = 
                window
                .location
                .href
                .replace("addCustomer", "saveCustomer") + "?studentId=" + studentId;
            window.location.href = nextURL;
        });
    }
}

// Displays a loading message while the page isn't loaded
// then, runs the code in main once it is loaded.
displayLoadingOverlay();
let loading = function() {
    if (window.isDbLoaded) { 
        main();
        hideLoadingOverlay();
    } else {
        setTimeout(loading, 0);
    }
};
setTimeout(loading, 0);

// Display loading message.
function displayLoadingOverlay() {
    document.getElementById("loading-overlay").style.display = "block";
    document.getElementById("content").style.display = "none";
}

function hideLoadingOverlay() {
    document.getElementById("loading-overlay").style.display = "none";
    document.getElementById("content").style.display = "block";
}
