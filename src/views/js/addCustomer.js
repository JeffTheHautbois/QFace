
// The code that runs after emscripten/db is fully loaded.
let main = function() {
    Module.addCustomer_init();
    let photosTaken = false;

    let displayMostRecentlyDetectedImage = function () {
        let imageContainer = document.getElementById("images");
        imageContainer.style.display = "flex";
        let newImage = document.createElement("img");
        newImage.src = "data:image/png;base64," + Module.addCustomer_mostRecentDetectedFace();
        newImage.classList.add("croppedImage");
        imageContainer.appendChild(newImage);
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

    // Ran when the Take Picture button is clicked.
    document.getElementById("tpButton").onclick = function(){
        let dataURI = getFrame();

        // Crop the face and save it to temporary storage.
        let success = Module.addCustomer_saveFaceInTemporaryStorage(dataURI);
        if (!success) {
            return;
        }
        photosTaken = true;
        displayMostRecentlyDetectedImage();
    };

    // Automatically detect faces
    document.getElementById("detectFace").onclick = function(){
        let imagesTaken = 0;
        let imagesToTake = 8;
        let delay = 100;

        let singlePictureButton = document.getElementById("tpButton");
        let saveButton = document.getElementById("save-button");
        let clearButton = document.getElementById("clear-button");

        this.disabled = true;
        singlePictureButton.disabled = true;
        saveButton.disabled = true;
        clearButton.disabled = true;

        let takePictureFromVideo = () => {
            if (imagesTaken >= imagesToTake) {
                this.disabled = false;
                singlePictureButton.disabled = false;
                saveButton.disabled = false;
                clearButton.disabled = false;
                return;
            }

            let dataURI = getFrame();

            // Crop the face and save it to temporary storage.
            let success = Module.addCustomer_saveFaceInTemporaryStorage(dataURI);
            if (!success) {
                return;
            }

            photosTaken = true;
            displayMostRecentlyDetectedImage();

            imagesTaken += 1;
            setTimeout(takePictureFromVideo, 400);
        }

        takePictureFromVideo();
    };

    // Ran when the "save" button is clicked.
    document.getElementById("save-button").onclick = function() {
        if (!photosTaken) {
            alert("No pictures taken - press the \"Take Picture\" button.")
            return;
        }

        let studentId = window.parseInt(document.getElementById("studentId-form").value);
        if (!studentId) {
            alert("Invalid studentId");
            return;
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

    document.getElementById("clear-button").onclick = function() {
        Module.clearTemporaryStorage();
        let imageContainer = document.getElementById("images");
        while (imageContainer.hasChildNodes()) {
            imageContainer.removeChild(imageContainer.lastChild);
        }
        imageContainer.style.display = 'none';
    }
}
