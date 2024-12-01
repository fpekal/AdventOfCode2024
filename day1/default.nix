{ pkgs ? import <nixpkgs> {} }:
let
	input_raw = builtins.readFile ./input.txt;
	input_changed = pkgs.writeText "input.txt" ("[" + input_raw + "]");
	input = import input_changed;

	numbers = builtins.genList (x: x) (builtins.length input);
	numbered_input =
		builtins.map (
			x:
			{
			 idx = x;
			 value = (builtins.elemAt input (x));
			}
		) numbers;

	input_first = builtins.map (x: x.value) (builtins.filter (x: (pkgs.lib.trivial.mod x.idx  2) == 0) numbered_input);
	input_second = builtins.map (x: x.value) (builtins.filter (x: (pkgs.lib.trivial.mod x.idx 2) == 1) numbered_input);

	input_first_sorted = builtins.sort builtins.lessThan input_first;
	input_second_sorted = builtins.sort builtins.lessThan input_second;

	numbers_half = builtins.genList (x: x) (builtins.length input_first);
	inputs_merged =
		builtins.map (
			x:
			{
			 first = (builtins.elemAt input_first_sorted (x));
			 second = (builtins.elemAt input_second_sorted (x));
			}
		) numbers_half;
	
	absolute_value = (x: if x > 0 then x else -x);
	distance = builtins.map (x: absolute_value (x.first - x.second)) inputs_merged;
	part1 = builtins.foldl' (x: y: x + y) 0 distance;

	count_if_equal = (num: list: builtins.foldl' (x: y: x + y) 0 (builtins.map (x: if x == num then 1 else 0) list));

	weighted = builtins.map (x: x * (count_if_equal x input_second)) input_first;
	part2 = builtins.foldl' (x: y: x + y) 0 weighted;
in
pkgs.stdenv.mkDerivation {
	name = "day1";

	phases = [ "installPhase" ];

	installPhase = ''
	echo ${builtins.toString part2} > $out
	'';
}
