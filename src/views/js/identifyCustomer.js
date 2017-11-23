// The code that runs after emscripten/db is fully loaded.
let main = function() {
    let facesToDetect = Module.identifyCustomer_init();
    let saveButton = document.getElementById("save-button");
    let detectedFace = document.getElementById("detectedFace");
    
    if (!facesToDetect) {
      alert('No faces found. Please add some faces to the database.');
      window.location.href = '/addCustomer';
    }

    let photosTaken = false;
    let studentId = NaN;

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

        let delay = 100;

        let imageCounter = document.getElementById("imageCounter")
        let errorDisplay = document.getElementById("errorMessages")

        //this.disabled = true;
        saveButton.disabled = true;
        imageCounter.style.display = 'block';

        // Display console log messages to user.
        let oldLogger = window.console.log;
        window.console.log = function(message) {
            errorDisplay.innerText = message;
            oldLogger(message);
        }

        let takePictureFromVideo = function() {

            let dataURI = getFrame();

            // Crop the face and save it to temporary storage.
            let success = Module.identifyCustomer_saveFaceInTemporaryStorage(dataURI);

            if (success) {
                photosTaken = true;
                let croppedFace = Module.identifyCustomer_getCroppedFace();
                let customer = JSON.parse(Module.identifyCustomer_identify(croppedFace));
                studentId = customer.studentId;


                let previousImageOfCustomer = Module.getImagesOfUser(studentId, 1)[0];

                let imageContainer = document.getElementById("detectedImage");
                imageContainer.style.display = "block";
                imageContainer.src = "data:image/png;base64," + previousImageOfCustomer;
                imageContainer.classList.add("fadeIn");

                document.getElementById("predictedName").innerText = "Detected: " + customer.name;
                document.getElementById("predictedStudentId").innerText = "StudentId: " + studentId;

                // Make buttons clickable.
                this.disabled = false;
                saveButton.disabled = false;
                errorDisplay.innerText = "";
                imageCounter.style.display = 'none';
                detectedFace.style.display = 'flex';
                window.console.log = oldLogger;
                return;
            }

            setTimeout(takePictureFromVideo, 400);
        }

        takePictureFromVideo();
    };

    // Ran when the "save" button is clicked.
    document.getElementById("save-button").onclick = function() {
        if (isNaN(studentId)) {
            alert("Have not yet any faces.");
            return;
        }

        Module.identifyCustomer_confirm(studentId);
        Module.identifyCustomer_clean();
        Module.persist().then(() => {
            let nextURL =
                window
                .location
                .href
                .replace("identifyCustomer", "showCustomer") + "?studentId=" + studentId;
            window.location.href = nextURL;
        });
    }

    let clearFaces = function() {
        Module.clearTemporaryStorage();
        let imageContainer = document.getElementById("detectedImage");
        imageContainer.src = "";
    }
}
