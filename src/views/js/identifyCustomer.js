// The code that runs after emscripten/db is fully loaded.
let main = function() {
    Module.identifyCustomer_init();
    let photosTaken = false;

    let displayMostRecentlyDetectedImage = function () {
        let imageContainer = document.getElementById("detectedImage");
        imageContainer.style.display = "block";
        imageContainer.src = "data:image/png;base64," + Module.identifyCustoner_getCroppedFace();
        imageContainer.classList.add("fadeIn");
    }

    // Returns the webcam frame as a b64 string.
    let getFrame = function () {
        let canvas = document.createElement('canvas');
        let ctx = canvas.getContext('2d');

        //draw image to canvas. scale to target dimensions
        ctx.drawImage(video, 0, 0, canvas.width, canvas.height);

        //convert to desired file format
        let dataURI = canvas.toDataURL('image/png').replace('data:image/png;base64,','');

        return dataURI;
    }

    // Automatically detect faces
    document.getElementById("detectFace").onclick = function(){
        clearFaces();

        let imagesTaken = 0;
        let imagesToTake = 1;
        let delay = 100;

        let saveButton = document.getElementById("save-button");
        let clearButton = document.getElementById("clear-button");

        let imageCounter = document.getElementById("imageCounter")
        let errorDisplay = document.getElementById("errorMessages")

        this.disabled = true;
        saveButton.disabled = true;
        clearButton.disabled = true;
        imageCounter.style.display = 'block';

        // Display console log messages to user.
        let oldLogger = window.console.log;
        window.console.log = function(message) {
            errorDisplay.innerText = message;
        }

        let takePictureFromVideo = () => {
            if (imagesTaken >= imagesToTake) {
                window.console.log = oldLogger;
                this.disabled = false;
                saveButton.disabled = false;
                clearButton.disabled = false;
                imageCounter.style.display = 'none';
                return;
            }

            let dataURI = getFrame();

            // Crop the face and save it to temporary storage.
            let success = Module.identifyCustoner_saveFaceInTemporaryStorage(dataURI);

            if (success) {
                errorDisplay.innerText = "";
                // Only record and display a picture when it was successfully
                // detected.
                photosTaken = true;
                displayMostRecentlyDetectedImage();

                imageCounter.innerText = "Images taken: " + imagesTaken + "/" + imagesToTake;
                imagesTaken += 1;
            }

            setTimeout(takePictureFromVideo, 400);
        }

        takePictureFromVideo();
    };

    // Ran when the "save" button is clicked.
    document.getElementById("save-button").onclick = function() {
        Module.identifyCustoner_clean();
        Module.persist().then(() => {
            let nextURL =
                window
                .location
                .href
                .replace("identifyCustomer", "verify");
            window.location.href = nextURL;
        });
    }

    let clearFaces = function () {
        Module.clearTemporaryStorage();
        let imageContainer = document.getElementById("detectedImage");
        imageContainer.src = "";
        imageContainer.style.display = 'none';
    }

    document.getElementById("clear-button").onclick = clearFaces();
}
