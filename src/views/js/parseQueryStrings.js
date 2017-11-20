function getStudentIDFromQueryString () {
	//Parse StudentID
    let splitURL = window.location.href.split('?');  // split inputs
    if (splitURL.length == 1 ){
        return NaN;
    }

    let queryStrings = splitURL[1].split('&');

    let studentId = queryStrings.find((element) => {
        return element.indexOf('studentId=') >= 0;
    });

    return window.parseInt(studentId.split('=')[1]);  
}