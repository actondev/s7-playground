project('s7-playground', 'c',
       	default_options: ['default_library=static']
       )

s7 = subproject('s7')
s7_dep = s7.get_variable('s7_dep')

sources = files(
  'src/s7_wasm.c',
  )

executable('s7_wasm',
	   sources,
	   dependencies: [s7_dep],
	   # c_args: ['-sASSERTIONS=1'],
	   name_suffix: 'js')
