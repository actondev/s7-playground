project('s7-playground', 'c',
       	default_options: ['default_library=static']
       )

s7 = subproject('s7')
s7_dep = s7.get_variable('s7_dep')

sources = files(
  'src/s7_wasm.c',
  )

#   Note:
#     Options can be specified as a single argument without a space
#    between the "-s" and option name.  e.g. "-sFOO=1".

executable('s7_wasm',
	   sources,
	   dependencies: [s7_dep],
	   c_args: [
	     # note: this is called when compiling the c files to object files
	   ],
	   link_args: [
	     # this is the second pass, emcc -o s7_wasm.js ...
	     '-sEXTRA_EXPORTED_RUNTIME_METHODS=["ccall"]',
	     '-sEXPORTED_FUNCTIONS=["_main", "_eval_string"]',
	     ],
	   name_suffix: 'js')
