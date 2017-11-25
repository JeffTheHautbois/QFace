// The code that runs after emscripten/db is fully loaded.
let main = function() {
    //Invoke parseQueryStrings()
    let studentId = getStudentIDFromQueryString();

    if (window.isNaN(studentId) || studentId < 0){
        alert("Missing Student Id");
        window.location.href = "/";
    }

    displayNewFaces();

    let customer = JSON.parse(Module.getCustomer(studentId));
    let nameInput = document.getElementById("name");
    let ageInput = document.getElementById("age");

    if (!customer.studentId) {
        document.getElementById("saveCustomerHeading").innerText = "Saving new customer with Student ID: " + studentId;
    } else {
        document.getElementById("saveCustomerHeading").innerText = "Updating customer with Student ID: " + studentId;
        nameInput.value = customer.name;
        ageInput.value = customer.age;
        displayOldFaces(studentId, 1);
    }

    // Ran when the "save" button is clicked.
    document.getElementById("saveButton").onclick = function() {
        let name = nameInput.value;
        let age = window.parseInt(ageInput.value);

        if (window.isNaN(age)){
            alert("Age not valid!");
            return;
        }

        customer.name = name;
        customer.age = age;
        customer.studentId = studentId;

        Module.saveCustomer_saveCustomer(studentId, JSON.stringify(customer));
        Module.persist().then(() => {
            let nextURL = 
                window
                .location
                .href
                .replace("saveCustomer", "showCustomer");
            window.location.href = nextURL;
        });
    }
}

let displayNewFaces = function() {
    let images = Module.getImagesInTemporaryStorage();
    if (images.length <= 0) {
        alert("No Faces Found!");
        window.location.href = "/";
    }

    // Display the updated faces.
    let imageContainer = document.getElementById("newImages");
    for (let i = 0; i < images.length; i++) {
        let newImage = document.createElement("img");
        newImage.src = "data:image/png;base64," + images[i];
        newImage.classList.add("croppedImage");
        imageContainer.appendChild(newImage);
    }
}

let displayOldFaces = function(studentId, numberOfFaces) {
   let images = Module.getImagesOfUser(studentId, numberOfFaces);
   let imageContainer = document.getElementById("oldImages");
    imageContainer.style.display = 'block';
    for (let i = 0; i < images.length; i++) {
        let newImage = document.createElement("img");
        newImage.src = "data:image/png;base64," + images[i];
        newImage.classList.add("croppedImage");
        imageContainer.appendChild(newImage);
    }
}
