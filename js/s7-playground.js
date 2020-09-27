function escapeHtml(unsafe) {
    // https://stackoverflow.com/a/6234804
    return unsafe
         .replace(/&/g, "&amp;")
         .replace(/</g, "&lt;")
         .replace(/>/g, "&gt;")
         .replace(/"/g, "&quot;")
         .replace(/'/g, "&#039;");
 }

function createPreWithClass(className){
    const el = document.createElement("pre");
    el.className = className;
    return el;
}

function setup() {
    const codeElements = document.getElementsByClassName("code");
    // looping in reverse. if not, replacing the code elements with codemirror will not work
    for (var i = codeElements.length-1; i >= 0; i--) {
	const codeElement = codeElements[i];
	const parent = codeElement.parentNode;
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
	    // newline is important before closing paren!
	    // (in case of last line comments)
	    const wrappedCode = "(begin " + cm.getValue() + "\n)";
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

	    // the document *might* have a div with class eval-result
	    // which is when manually running the code with the apropriate parsing
	    // (even all the blocks could be evaluated already!)
	    // so, in case it exists we just replace with res, out, err
	    // if not, we create this block
	    let evalResult = parent.nextElementSibling;
	    if(evalResult.className != "eval-result") {
		evalResult = document.createElement("div");
		evalResult.className = "eval-result";

		const elRes = createPreWithClass('res');
		const elOut = createPreWithClass('out');
		const elErr = createPreWithClass('err');

		evalResult.appendChild(elRes);
		evalResult.appendChild(elOut);
		evalResult.appendChild(elErr);

		// appending evalResult next to our code
		parent.parentNode.insertBefore(evalResult, parent.nextElementSibling);
	    }

	    evalResult.querySelector('.res').innerHTML = escapeHtml(res);
	    evalResult.querySelector('.out').innerHTML = escapeHtml(out);
	    evalResult.querySelector('.err').innerHTML = escapeHtml(err);
	}
    }
}

window.onload = function() {
    setup();
}
