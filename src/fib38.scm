(define-macro (time expr) 
	  `(let ((start (*s7* 'cpu-time)))
	     (let ((res (list ,expr))) ; expr might return multiple values
	       (list (car res)
		     (- (*s7* 'cpu-time) start)))))

(define (fib n) 
  (if (< n 2) n (+ (fib (- n 1)) (fib (- n 2)))))

(display "fib38\n")
(display (time (fib 38)))
