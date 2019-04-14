
/*JEU DE DES DE MOZART
PHILHARMONIE DES ENFANTS
CODE ECRIT PAR THOMAS DESAI*/


// boot server

s.boot;

SerialPort.listDevices; // check which ports the ESP32 are connected to.

~port1 = ArduinoSMS("COM5", 115200); // tell SC to read the serial ports for the computer.
~port2 = ArduinoSMS("COM5", 115200);
~port3 = ArduinoSMS("COM5", 115200);
~port4 = ArduinoSMS("COM5", 115200);
~port5 = ArduinoSMS("COM5", 115200);
~port6 = ArduinoSMS("COM5", 115200);


/*
// to close the ports when necessary.
~port1.close;
~port2.close;
~port3.close;
~port4.close;
~port5.close;
~port6.close;
SerialPort.closeAll;
*/

~port6.close;

//////////////////////////////////// load buffers - run seperately first to implement buffers correctly
/*
	j = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/1.wav");
	k = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/2.wav");
	l = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/3.wav");
	m = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/4.wav");
	n = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/5.wav");
	o = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/6.wav");
	p = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/7.wav");
	q = Buffer.read(s, Platform.resourceDir +/+ "sounds/sitar/8.wav");
*/


	~a1 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/a1.wav");
	~a2 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/a2.wav");
	~a3 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/a3.wav");
	~a4 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/a4.wav");
	//~a5 = Buffer.read(s, Platform.resourceDir +/+ "sounds/mozart/M21.wav");

	~b1 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/b1.wav");
	~b2 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/b2.wav");
	~b3 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/b3.wav");
	~b4 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/b4.wav");
    //~b5 = Buffer.read(s, Platform.resourceDir +/+ "sounds/mozart/M22.wav");


	~c1 = Buffer.read(s, Platform.resourceDir +/+"sounds/PhilaFolia/c1.wav");
	~c2 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/c2.wav");
    ~c3 = Buffer.read(s, Platform.resourceDir +/+"sounds/PhilaFolia/c3.wav");
	~c4 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/c4.wav");
	//~c5 = Buffer.read(s, Platform.resourceDir +/+"sounds/mozart/M23.wav");

	~d1 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/d1.wav");
    ~d2 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/d2.wav");
	~d3 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/d3.wav");
	~d4 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/d4.wav");
	//~d5 = Buffer.read(s, Platform.resourceDir +/+ "sounds/mozart/M24.wav");


	~e1 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/e1.wav");
	~e2 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/e2.wav");
	~e3 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/e3.wav");
	~e4 = Buffer.read(s, Platform.resourceDir +/+ "sounds/PhilaFolia/e4.wav");
	//~e5 = Buffer.read(s, Platform.resourceDir +/+ "sounds/mozart/M25.wav");



// SynthDef for buffers

SynthDef("BufTing",{ arg out = 0, bufnum; // bufnum the key variable
    Out.ar( out,
        PlayBuf.ar(2, bufnum, BufRateScale.kr(bufnum)) // change number of channels based on sample chosen.
    )
}).add;


//OSC 'SOUND SELECT' CONTROLS - add as many choices per section as neccessary
// MUST CHANGE TO SERIAL INPUT! ~ should be quick but must do!


// SELECTION 1

/*
//OSC
a = (OSCdef.new(\section1, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{a = ~a1});
	if(
		msg[1] == 2,
		{a = ~a2});
	if(
		msg[1] == 3,
		{a = ~a3});
	if(
		msg[1] == 4,
		{a = ~a4});
	/*if(
		msg[1] == 5,
		{a = ~a5});*/

},'/oscControl/1'));

*/

// SERIAL READ

~port1.action = { |... msg|
		m=[msg[0],msg[1]].postln; //Parse message stream. use m[0] as identifier and m[1] as value
		case
			{m[0]=="a"} {
				case
					{m[1]==1}{a = ~a1;}
					{m[1]==2}{a = ~a2;}
		            {m[1]==3}{a = ~a3;}
					{m[1]==4}{a = ~a4;}
		            {m[1]==5}{a = ~a5;}
};
}; // this solution works like an absolute dream.



//SELECTION 2


// OSC
/*
b = (OSCdef.new(\section2, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{b = ~b1});
	if(
		msg[1] == 2,
		{b = ~b2});
	if(
		msg[1] == 3,
		{b = ~b3});
	if(
		msg[1] == 4,
		{b = ~b4});
	/*if(
		msg[1] == 5,
		{b = ~b5});*/
},'/oscControl/2'));
*/



// SERIAL READ
~port2.action = { |... msg|
		m=[msg[0],msg[1]].postln; //Parse message stream. use m[0] as identifier and m[1] as value
		case
			{m[0]=="b"} {
				case
					{m[1]==1}{b = ~b1;}
					{m[1]==2}{b = ~b2;}
		            {m[1]==3}{b = ~b3;}
					{m[1]==4}{b = ~b4;}
		            {m[1]==5}{b = ~b5;}
};
};


//SELECTION 3


/*
//OSC
c = (OSCdef.new(\section3, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{c = ~c1});
	if(
		msg[1] == 2,
		{c = ~c2});
	if(
		msg[1] == 3,
		{c = ~c3});
	if(
		msg[1] == 4,
		{c = ~c4});
	/*if(
		msg[1] == 5,
		{c = ~c5});*/
},'/oscControl/3'));
*/


// SERIAL READ
~port3.action = { |... msg|
		m=[msg[0],msg[1]].postln; //Parse message stream. use m[0] as identifier and m[1] as value
		case
			{m[0]=="c"} {
				case
					{m[1]==1}{c = ~c1;}
					{m[1]==2}{c = ~c2;}
		            {m[1]==3}{c = ~c3;}
					{m[1]==4}{c = ~c4;}
		            {m[1]==5}{c = ~c5;}
};
};


//SELECTION 4

/*
// OSC
d = (OSCdef.new(\section4, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{d = ~d1});
	if(
		msg[1] == 2,
		{d = ~d2});
	if(
		msg[1] == 3,
		{d = ~d3});
	if(
		msg[1] == 4,
		{d = ~d4});
	/*if(
		msg[1] == 5,
		{d = ~d5});*/
},'/oscControl/4'));
*/

// SERIAL READ
~port4.action = { |... msg|
		m=[msg[0],msg[1]].postln; //Parse message stream. use m[0] as identifier and m[1] as value
		case
			{m[0]=="d"} {
				case
					{m[1]==1}{d = ~d1;}
					{m[1]==2}{d = ~d2;}
		            {m[1]==3}{d = ~d3;}
					{m[1]==4}{d = ~d4;}
		            {m[1]==5}{d = ~d5;}
};
};



//SELECTION 5


/*
//OSC
e = (OSCdef.new(\section3, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{e = ~e1});
	if(
		msg[1] == 2,
		{e = ~e2});
	if(
		msg[1] == 3,
		{e = ~e3});
	if(
		msg[1] == 4,
		{e = ~e4});
	/*if(
		msg[1] == 5,
		{e = ~e5});*/
},'/oscControl/five'));
*/

// SERIAL READ
~port5.action = { |... msg|
		m=[msg[0],msg[1]].postln; //Parse message stream. use m[0] as identifier and m[1] as value
		case
			{m[0]=="e"} {
				case
					{m[1]==1}{e = ~e1;}
					{m[1]==2}{e = ~e2;}
		            {m[1]==3}{e = ~e3;}
					{m[1]==4}{e = ~e4;}
		            {m[1]==5}{e = ~e5;}
};
};

// TO PLAY & CONTROL SOUNDS

//OSC
/*
(OSCdef.new(\Play, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{g ={
	Synth(\BufTing, [\bufnum,a]);

	5.225.wait; // set wait to fit the chosen samples. - should be 5.225 nominally

	Synth(\BufTing, [\bufnum,b]);

	5.225.wait;

	Synth(\BufTing, [\bufnum,c]);

	5.225.wait;

	Synth(\BufTing, [\bufnum,d]);

	5.225.wait;

	Synth(\BufTing, [\bufnum,e]);

	5.225.wait;

}.fork;});
},'/oscControl/play');); // when called plays stack following defined algo. - variation made within OSC track select settings.



(OSCdef.new(\Silence, {
	arg msg,time,addr,port;
	msg.postln;
	if(
		msg[1] == 1,
		{h =(s.freeAll)});
},'/oscControl/stop')); // currently only kills active track -- should change to kill stack

*/

/// SERIAL

~port6.action = { |... msg|
	y=msg[0].postln;
	if (y == "PLAY") {g = {
	Synth(\BufTing, [\bufnum,a]);

	5.225.wait; // set wait to fit the chosen samples. - should be 5.225 nominally

	Synth(\BufTing, [\bufnum,b]);

	5.225.wait;

	Synth(\BufTing, [\bufnum,c]);

	5.225.wait;

	Synth(\BufTing, [\bufnum,d]);

	5.225.wait;

	Synth(\BufTing, [\bufnum,e]);

	5.225.wait;

}.fork} {"STOP".postln};
}

// still need to get this working for the play function.



