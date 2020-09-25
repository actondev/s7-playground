function setupCodeMirror() {
    const codeElements = document.getElementsByClassName("code");
    console.log(codeElements);
    for (var i = codeElements.length-1; i >= 0; i--) {
	const codeElement = codeElements[i];
	const parent = codeElement.parentNode;
	// console.log("i", i, "code el", codeElement);
	const cm = CodeMirror(function(elt) {
	    codeElement.parentNode.replaceChild(elt, codeElement);
	}, {value: codeElement.value,
	    // lineNumbers: true,
	    mode: "scheme",
	    theme: "monokai",
	    styleActiveLine: true,
	    autoCloseBrackets: true,
	    matchBrackets: true,
	   });
	parinferCodeMirror.init(cm);
	console.log("parent", parent);
	const evalButton = parent.querySelector('.eval');
	evalButton.onclick = function() {
	    const wrappedCode = "(begin " + cm.getValue() + ")";
	    Module.ccall('eval_string', // name of C function
			 null, // return type
			 ['string'], // argument types
			 [wrappedCode]); // arguments
	}
    }
}

window.onload = function() {
    setupCodeMirror();
}
