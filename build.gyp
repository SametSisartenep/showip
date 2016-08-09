{
	"targets": [
		{
			"target_name": "showip",
			"type": "executable",
			"sources": [
				"src/showip.c"
			],
			"conditions": [
				["OS == 'linux'", {
					"defines": [
						"_FORTIFY_SOURCE=2"
					],
					"cflags": [
						"-Wall",
						"-Wextra",
						"-Werror",
						"-Wformat-security",
						"-Wpointer-arith",
						"-Wformat-nonliteral",
						"-Winit-self",
						"-fno-exceptions",
						"-fstack-protector-strong",
						"--param=ssp-buffer-size=4",
						"-Wpedantic",
						"-pedantic",
						"-pipe",
						"-Wl,--no-undefined",
						"-Wl,--build-id=sha1",
						"-O2"
					],
					"ldflags": [
						"-zrelro",
						"-znow",
						"-O1a",
						"-s",
					],
				}],
			],
		},
	],
}
