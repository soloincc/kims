/*
contains the planning scripts
*/

//we updating the month details as selected by the user
function getMonth(id){
	getObject('flagid').value='getmonth';
	getObject('monthid').value=id;
	var form=document.forms[0];
	
	//the post values are not being sent with the POST request, so lets see if by  serializing them they will be sent
	var params=serializeData(form);
    ajaxRequest('seamless.php', 'updateMonth(httpRequest)', 'text/html', params);
}

function updateMonth(data){
//we have the month selected in qst, so delete the 
	if(data.readyState==4){
		if(data.status==200 || data.status==304){
			getObject('bone').innerHTML=data.responseText;
		}else{
		}
	}
}

function postEvent(){
	//we wanna post a submitted event, so do the checks and then the posting
	var day, mon, yr, type, other, caption, text, temp,error=false;
	day=getObject('dayid').value; mon=getObject('monid').value;
	yr=getObject('yearid').value; type=getObject('typeid').value;
	other=getObject('otherid').value; caption=getObject('captionid').value;
	text=getObject('textid').value;
	
	temp=getObject('datelabel');
	if(day==0 || mon==0 || yr==0){ 
		showError(temp); error=true;
	}else{
		if(hasClass(temp, 'error')){ removeClass(temp,'error'); addClass(temp,'norm'); }
	}
	if((type=='other' && (!validate('specify',7) || other=='specify')) || (type==0 && other=='specify')){
		temp=getObject('otherlabel'); showError(temp);
		temp=getObject('typelabel'); showError(temp);
		error=true;
	}else{
		temp=getObject('otherlabel');
		if(hasClass(temp, 'error')){ removeClass(temp,'error'); addClass(temp,'norm'); }
		temp=getObject('typelabel');
		if(hasClass(temp, 'error')){ removeClass(temp,'error'); addClass(temp,'norm'); }
	}
	temp=getObject('captionlabel');
	if(!validate(caption,0) || !validate(caption,7)){
		showError(temp); error=true;
	}else{
		if(hasClass(temp, 'error')){ removeClass(temp,'error'); addClass(temp,'norm');}
	}
	temp=getObject('textlabel');	
	if(text!=''){
		if(!validate(text,0) && !validate(text,7)){ showError(temp); error=true;}
	}else{
		if(hasClass(temp, 'norm')){ removeClass(temp,'norm'); addClass(temp,'error'); error=true;}
	}
	if(error){
		temp=getObject('errmessageid');
		if(hasClass('norm')){ removeClass(temp, 'norm'); addClass(temp,'errormssg');}
		temp.firstChild.nodeValue='iko makosa. check the fields in red!!';
	}else{
		blank('addevent');
		getObject('eventflagid').value='postevent';
		var form=document.forms['addingevent'];
		httpRequest=makeRequest();
	
		//the post values are not being sent with the POST request, so lets see if by  serializing them they will be sent
		var params=serializeData(form);
		httpRequest.onreadystatechange = function() { eventUpdated(httpRequest); };
		httpRequest.open("POST", 'seamless.php', true);
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		httpRequest.send(params);
	}
	//alert(day+mon+yr+type+other+caption+text);
	//if(dayid)
}

function updateContent(data){
//we have the month selected in qst, so delete the 
	if(data.readyState==4){
		if(data.status==200 || data.status==304){
			var temp=getObject('content');
			temp.innerHTML=data.responseText;
		}else{
		}
	}
}

function eventUpdated(data){
    var oldTemp;
	if(data.readyState==4){
		if(data.status==200 || data.status==304){
			//all is ok, bt lets check the code returned
			var returns=data.responseText.split(',');
			temp=getObject('addevent');
			oldTemp=getObject('errmessageid');
			oldTemp.firstChild.nodeValue=returns[1];
			unblank();
			if(returns[0]==true){
				//there was an error
				if(hasClass(temp, 'norm')){ removeClass(temp,'norm'); addClass(temp,'error');}
			}else{
				oldTemp.firstChild.nodeValue=returns[1];
				if(hasClass(temp, 'error')){ removeClass(temp,'error'); addClass(temp,'norm');}
				getObject('dayid').value=0; getObject('monid').value=0; getObject('typeid').value=0; getObject('yearid').value=0;
				getObject('otherid').value='specify'; getObject('captionid').value=''; getObject('textid').value='';
			}
		}else{
			//we have an error
			temp=getObject('addevent');
			oldTemp=getObject('errmessageid').value='iko makosa';
		}
	}
}

function getEvents(id){
	getObject('flagid').value='noticeboard';
	getObject('kindid').value=id;
	var form=document.forms[0];
	
	//the post values are not being sent with the POST request, so lets see if by  serializing them they will be sent
	var params=serializeData(form);
    ajaxRequest('seamless.php?page=plan', 'updateContent(httpRequest)', 'text/html', params);
}

function getContacts(){
}

function getEventContents(id){
	var params='flag=displayevent&eventId='+encodeURIComponent(id);
	ajaxRequest('seamless.php?page=plan','updateMonth(httpRequest)','text/html',params);
}

function getDateEvents(date, month){

}

function showError(temp){
	if(hasClass(temp,'norm')){
		removeClass(temp, 'norm');
		addClass(temp,'error');
	}
	else if(!hasClass(temp,'error')) addClass(temp,'error');
}