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
	    const res = Module.ccall('eval_string', // name of C function
			 'string', // return type
			 ['string'], // argument types
			 [wrappedCode]); // arguments

	    const out = Module.ccall('get_out', // name of C function
			 'string', // return type
			 [], // argument types
				     []); // arguments

	    const err = Module.ccall('get_err', // name of C function
			 'string', // return type
			 [], // argument types
				     []); // arguments

	    console.log("res:", res);
	    console.log("out:", out);
	    console.log("err:", err);

	    // note: gotta check for <empty string>
	}
    }
}

window.onload = function() {
    setupCodeMirror();
}
