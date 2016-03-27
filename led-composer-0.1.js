/*
 * Kalanda Led Composer v0.1
 *
 * Copyright (c) 2008 kalanda
 * Under Creative Commons License
 *
 */

// Used variables
var displaysBitmapsArray;
var frames, speed, mode, cols;
var cellWidth = 16;

// runs onLoad body
$(document).ready(function () { init(); });

// clear and create
function init() {

	displaysBitmapsArray = new Array();
    $("#codeResult").click(function(){ $("#codeResult").focus(); $("#codeResult").select() });

	// get values for creation
	speed = $("#num-speed").val();
	mode = $("#mode").val();
	frames = $('#num-frames').val();

	// choose bit columns
	if (mode==1) cols = 8;  else cols=7;

	// clear scroller div
	$("#scroller").empty();

	// Create a table for frames
	if (mode==1) {
		jQuery('<table id="frames" class="scroll" border="0" cellspacing="0" cellpadding="0" width="'+cellWidth*cols*frames+'"><tbody><tr></tr></tbody></table>').appendTo("#scroller");
	} else if (mode==2) {
		jQuery('<table id="frames" class="animation" border="0" cellspacing="0" cellpadding="0" width="'+cellWidth*cols*frames+'"><tbody><tr></tr></tbody></table>').appendTo("#scroller");
	}

	for (var frame=0;frame<frames;frame++){

		var frameBitmap = new Array();

		jQuery('<td id="frame'+frame+'" class="frame"></td>').appendTo("#frames > tbody > tr");

		var frameSrc = "";
		frameSrc += '<table border="0" cellspacing="0" cellpadding="0">';
		if (mode==2) frameSrc += '<caption>frame'+frame+'</caption>';

		for (var row=0;row<5;row++){
			frameSrc += '<tr>';

			for (var col=0;col<cols;col++){
				frameSrc += '<td class="off" width="'+cellWidth+'" onclick="toggleLed(this,'+frame+','+row+','+col+');"></td>';
				frameBitmap[row] = 0;
			}
			frameSrc += '</tr>';
		}
		frameSrc += '</table>';
		jQuery(frameSrc).appendTo("#frames > tbody > tr > #frame"+frame);
		displaysBitmapsArray.push(frameBitmap);
	}

	// show scroller and code
	$("#generator").hide();
	$("#editor").show();
	refreshResultCode();
}

function refreshResultCode(){

	var code = "";
	code += "// ------------------------------------------------------------------------\n";
	code += "// ----- Animation/Scroll setup (copy & paste into file animation.h ) -----\n";
	code += "// ------------------------------------------------------------------------\n";
	code += "#define SPEED "+speed+"\n";
	code += "#define MODE "+mode+" // 1:Scroll 2:Animation \n";
	code += "#define FRAMES "+frames+" // Up to 270 frames \n\n";
	code += "uint8_t animation[FRAMES][5] PROGMEM = {\n";

	for (var frame=0;frame<frames;frame++){
		frameObj = displaysBitmapsArray[frame];
		code += "{";
		for (var row=0;row<5;row++){
			code += frameObj[row]
			if (row<4) code += ",";
		}
		code += "}";
		if (frame<frames-1) code += ",";
		code += " //frame "+frame+"\n";
	}
	code += "};\n";
	$("#codeResult").empty().val(code);
}

function toggleLed(cell, frame, row, col){
	if (cell.className=='on') {
		cell.className='off';
	} else {
		cell.className='on';
	}
	frameObj = displaysBitmapsArray[frame];
	frameObj[row] ^= 1<<(cols-col-1);
	refreshResultCode();
}
