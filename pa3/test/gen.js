var template = {
	"base": "{1}",
	"1": [
		"@",
		"@{OP}@",
		"{1}{OP}{1}",
		"{1}{OP}@",
		"@{OP}{1}",
		"(@{OP}@)",
		"({1}){OP}({1})",
		"({1}){OP}@",
		"@{OP}({1})",
		"@{OP}@",
		"{1}{OP}{1}",
		"{1}{OP}@",
		"@{OP}{1}",
		"(@{OP}@)",
		"({1}){OP}({1})",
		"({1}){OP}@",
		"@{OP}({1})",
	],
	"OP": [
		"+",
		"-",
		"*",
		"/",
		"%",
		"|",
		"&",
		"\^",
		"+",
		"-",
		"*",
		"|",
		"&",
		"\^",
		"+",
		"-",
		"*",
		"|",
		"&",
		"\^",
		"+",
		"-",
		"*",
		"|",
		"&",
		"\^",
		"+",
		"-",
		"*",
		"|",
		"&",
		"\^"
	]
};

var regex_detector = /{(.*)}/;

var num       = +process.argv[2],
    intensity = +process.argv[3];


function expand(key) {
	key = key.slice(1, -1);
	return template[key][Math.floor(Math.random() * (template[key].length - 1))];
}

function generate_equation() {
	var str_ret = "";
	
	while (str_ret.length < intensity * 10) {
		str_ret = template["base"];
			
		while (str_ret.includes("{") || str_ret.includes("}")) {
			str_ret = str_ret.replace(/{(.*?)}/, expand);
			//console.log(str_ret);
		}

		while (str_ret.includes("@")) {
			str_ret = str_ret.replace(/@/, -10 + Math.floor(Math.random() * 20));
		}
	}

	return str_ret;
}

if (process.argv.length != 4) {
	console.log("Usage: node gen.js num intensity");
	process.exit(1);
}

for (var i = 0; i < num; i++) {
	var str = generate_equation();
	console.log(str + ";");
}
