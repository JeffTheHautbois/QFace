let main = function() {
    //Check studentid
    let studentId = getStudentIDFromQueryString();

    if (window.isNaN(studentId) || studentId < 0){
        alert("Missing Student Id");
        window.location.href = "/";
    }

    let customer = JSON.parse(Module.getCustomer(studentId));
    if (!customer.studentId) {
        alert("No customer found with Student ID: " + studentId);
        window.location.href = "/";
    }

        let images = Module.getImagesOfUser(studentId, -1);
    if (images.length <= 0) {
        alert("No Faces Found for Student ID: " + studentId);
        window.location.href = "/";
    }

    // Display the updated faces.
    let imageContainer = document.getElementById("images");
    for (let i = 0; i < images.length; i++) {
        let newImage = document.createElement("img");
        newImage.src = "data:image/png;base64," + images[i];
        newImage.classList.add("croppedImage");
        imageContainer.appendChild(newImage);
    }


    let nameHeader = document.getElementById("name");
    let ageHeader = document.getElementById("age");
    let studentIdHeader = document.getElementById("studentId");

    nameHeader.innerText += customer.name;
    ageHeader.innerText += customer.age;
    studentIdHeader.innerText += customer.studentId;

}
