//object detection
function getObject(elementId){
	if (document.all) return document.all(elementId);
	else if (document.getElementById) return document.getElementById(elementId);
	else if (document.layers) return document.layers[elementId];
}

function serializeData(form){
var params='';
var formElements=[];
	//get all the text areas
	var temp=form.getElementsByTagName('textarea');
	for(var i=0;i<temp.length;i++) formElements[formElements.length] = temp[i];
	//get all the selects
	var temp=form.getElementsByTagName('select');
	for(var i=0;i<temp.length;i++) formElements[formElements.length] = temp[i];
	//get all the input fields
	var temp=form.getElementsByTagName('input');
	for(var i=0;i<temp.length;i++){
		var tempType=temp[i].getAttribute('type');
		if(tempType==null || tempType=='text' || tempType=='hidden' || (typeof temp[i].checked!='undefined' && temp[i].checked==true))
			formElements[formElements.length] = temp[i];
	}
	//now serialize and encode all data
	for(i=0;i<formElements.length;i++){
		var elementName=formElements[i].getAttribute("name");
		if(elementName!=null && elementName!='') params+='&'+elementName+'='+encodeURIComponent(formElements[i].value);
	}
return params;
}

//we wanna get some of the words to go along
function makeRequest(url,formName, returnTo){
	if(window.XMLHttpRequest){ // Mozilla, Safari, ...
		httpRequest = new XMLHttpRequest();
		if (httpRequest.overrideMimeType) {
			httpRequest.overrideMimeType('text/html');
			// See note below about this line
		}
    } 
    else if(window.ActiveXObject){ // IE
		try{ httpRequest = new ActiveXObject("Msxml2.XMLHTTP");} 
        catch(e){
			try{ httpRequest = new ActiveXObject("Microsoft.XMLHTTP");} 
			catch(e){}
        }
	}

    if (!httpRequest) {
		alert('Giving up :( Cannot create an XMLHTTP instance');
        return false;
	}
	return httpRequest;
}

//hides or shows an elemnt
function showHide(objectId){
	var target=getObject(objectId);

	if(hasClass(target,'expanded')){
		removeClass(target,'expanded');
		addClass(target,'collapsed');
	}
	else if(hasClass(target,'collapsed')){
		removeClass(target,'collapsed');
		addClass(target,'expanded');
	}
}
  
function removeClass(target, theClass){
	var pattern = new RegExp("(^| )" + theClass + "( |$)");
	target.className = target.className.replace(pattern, "$1");
	target.className = target.className.replace(/ $/, "");
}

function addClass(target, theClass){
	if (!hasClass(target, theClass)){
		if (target.className == "") target.className = theClass;
		else target.className += " " + theClass;
	}
}

function hasClass(target, theClass){
  var pattern = new RegExp("(^| )" + theClass + "( |$)");
  if (pattern.test(target.className)) return true;
  return false;
}

function blank(objectId){
	//Create a  modal background
	modalWindow = document.createElement('div');
	modalWindow.setAttribute('id','modalWindowId');
	objectToCover=getObject(objectId);
	modalWindow.style.height = objectToCover.clientHeight +'px';
	modalWindow.style.width = objectToCover.clientWidth +'px';
	if (!this.isIE6){
		modalWindow.style.background = 'url(images/tp2.png)';  //transparent png with low opacity.  Provides a similar effect as opacy/filter settings, but without the memory leaks
	}
	modalWindow.style.position = 'absolute';
	modalWindow.style.left = '-10px';
	modalWindow.style.top = '-10px';
	modalWindow.style.zIndex = 998;
	modalWindow.style.visibility = 'hidden';
	objectToCover.appendChild(modalWindow);
	//document.html.modalWindow = modalWindow;	
	modalWindow.style.visibility = 'visible';
}

//removes the modal background created by blank
function unblank(){
	getObject('modalWindowId').style.visibility = 'hidden';
}

//used to validate an input. type is the option to choose
function validate(input,type){
//takes the input and the type of input we expecting. we try and match it with our regexp.
//return true if ok n false if not
	//required
	if(type==0){
		if(input==null || input=="") return false;
		else return true;
	}
	//no spaces allowed
	if(type==1) re=/\S+/g
	//positive integer
	if(type==2) re=/^d*[1-9]\d*$/g
	//positive or 0 integer
	if(type==3) re=/^\d+$/g
	//integer
	if(type==4) re=/^-?\d+$/g
	//decimal
	if(type==5) re=/^-?\d+(\.\d+)?$/g
	//email
	if(type==6) re=/^[\w\.\-]+@([\w\-]+\.)+[a-zA-Z]+$/g
	//no integers
	if(type==7) re=/[0-9]/g
	//illegal characters
	if(type==8) re=/\/#$|=~/g
	//tone words only
	if(type==9) re=/[^hls]/gi
	//phone numbers
	if(type==10) re=/^\+?\d/g
	//social sites nicks
	if(type==11) re=/^[\w\.\-]/gi
	//a value must be there in the get element
	if(type==12) re=/=.+&/g
	//undefined
	//if(re==/12/) alert('The option choosen is undefined.');
	
	if(input.match(re)==null) {/*alert('no errors'); */return true;}
	else return false;
}

function createMessageBox(message, callBack, cancelling, vars){
//variables are the variables that should be passed to the callback function. this will be held in an array
	var params="";
	var params=+(cancelling==true)?"":'';
	if(cancelling){
		var msg = new DOMAlert({
			title: 'kims personal page',
			text: message,skin: 'default',
			ok:{value: true, text: 'Yes', onclick: eval(callBack)},
			cancel: {value: false, text: 'No', onclick: eval(callBack)},
			variables: vars
		});
	}else{
		var msg = new DOMAlert({
			title: 'kims personal page',
			text: message,skin: 'default',
			ok:{value: true, text: 'Ok', onclick: eval(callBack)}
		});
	}
	msg.show();
}

//used by the message box when we just want to doNothing
function doNothing(sender, value){
	sender.close();
	//return -1;
}
