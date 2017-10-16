//!@ - Positive Integer
//@  - Positive/Negative Integer

var template = {
	"BASE": [
		"{1}", "{VAR}{ASSIGNMENT}{2}",
		"{1}", "{VAR}{ASSIGNMENT}{2}",
		"dump",
		"clear"
	],
	"1": [
		"{VAR}",
		"@",
		"@{OP}!@",
		"{1}{OP}{1}",
		"{1}{OP}!@",
		"@{OP}{1}",
		"(@{OP}@)",
		"({1}){OP}({1})",
		"({1}){OP}@",
		"@{OP}({1})",
		"@{OP}!@",
		"{1}{OP}{1}",
		"{1}{OP}!@",
		"!@{OP}{1}",
		"(@{OP}!@)",
		"({1}){OP}({1})",
		"({1}){OP}!@",
		"@{OP}({1})",
	],
	"2": [
		"{1}",
		"{VAR}{ASSIGNMENT}{2}"
	],
	"OP": [
		"+", "-", "*", "/", "%", "|", "&", "\^",
		"+", "-", "*",           "|", "&", "\^",
		"+", "-", "*",           "|", "&", "\^",
		"+", "-", "*",           "|", "&", "\^",
		"+", "-", "*",           "|", "&", "\^"
	],
	"VAR": [
		"a","b","c","d","e","f",
		"g","h","i","j","k","l",
		"m","n","o","p","q","r",
		"s","t","u","v","w","x",
		"y","z"
	],
	"ASSIGNMENT": [
		"=",
		"+=",
		"-=",
		"*=",
		"/=",
		"^=",
		"<<=",
		">>=",
		"&=",
		"^=",
		"|="
	]
};

var regex_detector = /{(.*)}/;

var num       = +process.argv[2],
    intensity = +process.argv[3];


function expand(key) {
	key = key.slice(1, -1);
	return template[key][Math.floor(Math.random() * (template[key].length))];
}

function generate_equation() {
	var str_ret = "";
	
	while (str_ret.length < intensity * 10) {
		str_ret = expand("{BASE}");
		if ((str_ret == "dump" || str_ret == "clear") && ((Math.random() * (100 * intensity)) > (100 * intensity) - 2))
			break;
			
		while (str_ret.includes("{") || str_ret.includes("}")) {
			str_ret = str_ret.replace(/{(.*?)}/, expand);
			//console.log(str_ret);
		}

		//Handle all forced positives first
		while (str_ret.includes("!@")) {
			abs_num = Math.floor(Math.random() * 20);
			str_ret = str_ret.replace(/\!@/, Math.floor(Math.random() * 20).toString());
		}

		//Handle all positives/negatives next.
		while (str_ret.includes("@")) {
			val_num = -10 + Math.floor(Math.random() * 20);

			if (val_num < 0)
				val_str = "(" + val_num.toString() + ")";
			else
				val_str = val_num.toString();

			str_ret = str_ret.replace(/@/, val_str);
		}
	}

	return str_ret;
}

if (process.argv.length != 4) {
	console.log("Usage: node gen_a.js num intensity");
	process.exit(1);
}

for (var i = 0; i < num; i++) {
	var str = generate_equation();
	console.log(str + ";");
}
