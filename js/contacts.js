var Contacts = {
   selTab: null,        //the currently selected tab when adding a contact
   contacts: null,      //holds all the contacts in a series of objects
   curView: null,       //defines the current viewing style
   curType: null,       //the current type 0-tel, 1-emails, 2-sites, 3-messengers, 4-address
   
   setType: function (type){
      this.curType=type;
   },
   
   setView: function (view){
      this.curView=view;
   },
   
   Tel: function (){
      this.mobile=new Array('','','');	//mobile numbers
      this.home=new Array('','','');	//3 home office
      this.office=new Array('','','');	//3 office tels
   },
   
   Email: function (){
      this.personal=new Array('','','');	//3 personal emails
      this.office=new Array('','','');	//3 office emails
      this.ppage='';this.opage='';this.blog='';
   },
   
   Ims: function (){
      this.ims=new Array('','','','',''); //all known ims in an array
      this.otitle=new Array('');	//stores other ims titles
      this.oids=new Array('');	//other ims user ids
   },
   
   AllContacts: function (){
      this.tels=new this.Tel();this.emails=new this.Email();this.ims=new this.Ims();
      this.address='';
   },
   
   generateTabs: function (tabs) {
      var sHTML = '';
      for(var i=0;i<tabs.length;i++){
         var tClass='none';
         if(i==0){
            var add="style='padding-left: 10px'";
            tClass='selected';
         }
         else var add='';
         sHTML += '<div id="tab' + (i+1) + '" class="'+tClass+'" '+add+' onmouseover="javascript:simulateTab(this.id);" ';
         sHTML+=' onfocus="javascript:simulateTab(this.id);" onmouseout="javascript:clearTab(this.id);" onblur="javascript:clearTab(this.id);" ';
         sHTML+='onclick="javascript:selectTab(this.id);" onkeypress="javascript:selectTab(this.id);">' + tabs[i] + '</div>';
      }
      selTab='tab1';
      document.getElementById('tabs').innerHTML = sHTML;
      this.generateTabContent(selTab);
      //create the objects needed
      this.contacts=new this.AllContacts();
   },
   
	showHideCategory: function (sElementId) {
		var sClassName = document.getElementById(sElementId).className;
		if(sClassName.match('selected')) return;
		else{
			if(sElementId != selTab) showHideElement(selTab + '-content');
			showHideElement(sElementId + '-content');
			selTab = sElementId;
			this.selectTab(sElementId);
		}
	},
   
	simulateTab: function (sElementId){
		if(selTab != sElementId){
			document.getElementById(sElementId).className = 'none highlight';
			//document.getElementById(sElementId).className = 'dark-tab-simulated';
		}
	},
   
	clearTab: function (sElementId){
		if(selTab != sElementId){
			document.getElementById(sElementId).className = 'none';
		}
		else document.getElementById(sElementId).className = 'selected';
	},
   
	selectTab: function (sElementId){
		if(selTab==sElementId) return;
		//b4 we generate any new items, collect the data that is inputted
		var check = this.collectTabInfo(selTab);
		if(check == -1) return;
		if(selTab!=undefined) document.getElementById(selTab).className = 'none';
		getObject(sElementId).className = 'selected';
		// assign selected tab to gloabal variable n generate new html
		selTab = sElementId;
		this.generateTabContent(sElementId);
	},
   
   generateTabContent: function (elemId){
	var shtml='';
		switch(elemId){
			case 'tab1':
				if(this.contacts && this.contacts.tels){var mob=this.contacts.tels.mobile;var hom=this.contacts.tels.home;var off=this.contacts.tels.office;}
				else{var mob=new Array('','','');var hom=new Array('','','');var off=new Array('','','');}
				shtml+="<div><label>mobile #s</label><br />";
				shtml+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='text' name='mob1' id='mob1' size='18' value='"+mob[0]+"'>  <input type='text' name='mob2' id='mob2' size='18' value='"+mob[1]+"'>";
				shtml+="  <input type='text' name='mob3' id='mob3' size='18' value='"+mob[2]+"'>";
				shtml+="</div><div><label>office #s</label><br />";
				shtml+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='text' name='off1' id='off1' size='18' value='"+hom[0]+"'>  <input type='text' name='off2' id='off2' size='18' value='"+hom[1]+"'>";
				shtml+="  <input type='text' name='off3' id='off3' size='18' value='"+hom[2]+"'>";
				shtml+="</div><div><label>home #s</label><br />";
				shtml+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='text' name='mob1' id='hom1' size='18' value='"+off[0]+"'>  <input type='text' name='hom2' id='hom2' size='18' value='"+off[1]+"'>";
				shtml+="  <input type='text' name='mob1' id='hom3' size='18' value='"+off[2]+"'>";
				shtml+="</div>";
			break;
			
			case 'tab2':
				if(this.contacts && this.contacts.emails){
					var per=this.contacts.emails.personal;var off=this.contacts.emails.office;
					var pweb=this.contacts.emails.ppage;var oweb=this.contacts.emails.opage;var blog=this.contacts.emails.blog;
				}
				else{
					var per=new Array('','','');var off=new Array('','','');
					var pweb='';var oweb='';var blog='';
				}
				shtml+="<div><label>personal emails</label><br />";
				shtml+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='text' name='mob1' id='per1' size='18' value='"+per[0]+"'>  <input type='text' name='mob1' id='per2' size='18' value='"+per[1]+"'>";
				shtml+="  <input type='text' name='mob1' id='per3' size='18' value='"+per[2]+"'>";
				shtml+="</div><div><label>office emails</label><br />";
				shtml+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='text' name='mob1' id='off1' size='18' value='"+off[0]+"'>  <input type='text' name='mob1' id='off2' size='18' value='"+off[1]+"'>";
				shtml+="  <input type='text' name='mob1' id='off3' size='18' value='"+off[2]+"'>";
				shtml+="</div><div><label style='padding-left:30px;'>personal webpage</label><label style='padding-left: 30px;'>office website</label><label style='padding-left: 45px;'>blog page</label><br />";
				shtml+="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='text' name='mob1' id='pweb' size='18' value='"+pweb+"'>  <input type='text' name='mob1' id='oweb' size='18' value='"+oweb+"'>";
				shtml+="  <input type='text' name='mob1' id='blog' size='18' value='"+blog+"'></div>";
			break;
			
			case 'tab3':
				if(this.contacts.address) var temp=this.contacts.address;
				else var temp='';
				shtml+="<div style='height: auto;'><label>physical address</label><br />";
				shtml+="<textarea name='text' id='addressid' cols='50' rows='4' style='margin-left: 40px;'>"+temp+"</textarea>";
				shtml+="</div>";
			break;
			
			case 'tab4':
				if(this.contacts && this.contacts.ims){var ims=this.contacts.ims.ims;var name=this.contacts.ims.otitle;var ids=this.contacts.ims.oids;}
				else{var ims=new Array('','','','','');var name=null;var ids=null;}
				shtml+="<div style='height: 132px;'><label style='padding-left: 120px;'>instant messengers and social sites</label>";
				shtml+="<div id='known'><label style='padding-left: 18px;'>gmail</label>&nbsp;<input type='text' name='mob1' id='gmail' size='20' value='"+ims[0]+"'><br />";
				shtml+="<label style='padding-left: 15px;'>yahoo</label>&nbsp;<input type='text' name='mob1' id='yahoo' size='20' value='"+ims[1]+"'><br />";
				shtml+="<label style='padding-left: 7px;'>hotmail</label>&nbsp;<input type='text' name='mob1' id='hotmail' size='20' value='"+ims[2]+"'><br />";
				shtml+="<label style='padding-left: 0px;'>facebook</label> <input type='text' name='mob1' id='fcbk' size='20' value='"+ims[3]+"'><br />";
				shtml+="<label style='padding-left: 32px;'>aol</label>&nbsp;<input type='text' name='mob1' id='aol' size='20' value='"+ims[4]+"'><br />";
				shtml+="</div><div id='unknown'><label>other ims</lable><br /><div id='inputs'><span>";
				if(name && name.length){
					var temp, temp1;
					for(i=0;i<name.length;i++){
						if(name[i] && ids[i]){
							temp=(name[i]==undefined)?'':name[i];temp1=(ids[i]==undefined)?'':ids[i];
							shtml+="<input type='text' name='mob1' id='name1' size='13' value='"+temp+"'>&nbsp;&nbsp;<input type='text' name='mob1' id='id1' size='13' value='"+temp1+"'><br />";
						}
						else shtml+="<input type='text' name='mob1' id='name1' size='13' value=''>&nbsp;&nbsp;<input type='text' name='mob1' id='id1' size='13' value=''><br />";
					}
				}
				else shtml+="<input type='text' name='mob1' id='name1' size='13' value=''>&nbsp;&nbsp;<input type='text' name='mob1' id='id1' size='13' value=''>";
				shtml+="<span><br /></div><span class='onemore'><a href='javascript:addOneMore();'>add one more</a></span></div></div>";
			break;
		}
		getObject('tabcontent').innerHTML=shtml;
	},
   
   collectTabInfo: function (elemId){
	var temp;
		switch(elemId){
			case 'tab1':
				for(j=1;j<4;j++){
					temp=getObject('mob'+j).value; 
					if(temp!='' && (validate(temp,10) || validate(temp,10) || temp.strlen>20)){
						createMessageBox('Error!! check Mobile '+j+'.','doNothing',false);
						return -1;
					}
					this.contacts.tels.mobile[j-1]=(temp==undefined || temp=='undefined')?'':temp;
				}
				for(j=1;j<4;j++){
					temp=getObject('off'+j).value; 
					if(temp!='' && (validate(temp,1) || validate(temp,10) || temp.strlen>20)){
						createMessageBox('Error!! check office number '+j+'.','doNothing',false);
						return -1;
					}
					this.contacts.tels.office[j-1]=(temp==undefined || temp=='undefined')?'':temp;
				}
				for(j=1;j<4;j++){
					temp=getObject('hom'+j).value; 
					if(temp!='' && (validate(temp,1) || validate(temp,10) || temp.strlen>20)){
						createMessageBox('Error!! check home number '+j+'.','doNothing',false);
						return -1;
					}
					this.contacts.tels.home[j-1]=(temp==undefined || temp=='undefined')?'':temp;
				}
			break;
			case 'tab2':
				for(j=1;j<4;j++){
					temp=getObject('per'+j).value; 
					if(temp!='' && (validate(temp,6) || temp.strlen>40)){
						createMessageBox('Error!! check personal email '+j+'.','doNothing',false);
						return -1;
					}
					this.contacts.emails.personal[j-1]=(temp==undefined || temp=='undefined')?'':temp;
				}
				for(j=1;j<4;j++){
					temp=getObject('off'+j).value; 
					if(temp!='' && (validate(temp,6) || temp.strlen>40)){
						createMessageBox('Error!! check office email '+j+'.','doNothing',false);
						return -1;
					}
					this.contacts.emails.office[j-1]=(temp==undefined || temp=='undefined')?'':temp;
				}
				temp=getObject('pweb').value; 
				if(temp!='' && (validate(temp,1) || temp.strlen>100)){
					createMessageBox('Error!! check personal website.','doNothing',false);
					return -1;
				}
				this.contacts.emails.ppage=(temp==undefined || temp=='undefined')?'':temp;
				temp=getObject('oweb').value; 
				if(temp!='' && (validate(temp,1) || temp.strlen>100)){
					createMessageBox('Error!! check office website.','doNothing',false);
					return -1;
				}
				this.contacts.emails.opage=(temp==undefined || temp=='undefined')?'':temp;
				temp=getObject('blog').value; 
				if(temp!='' && (validate(temp,1) || temp.strlen>100)){
					createMessageBox('Error!! check blog page.','doNothing',false);
					return -1;
				}
				this.contacts.emails.blog=(temp==undefined || temp=='undefined')?'':temp;
			break;
			case 'tab3':
				temp=getObject('addressid').value;this.contacts.address=(temp==undefined || temp=='undefined')?'':temp;
			break;
			case 'tab4':
				var ims=new Array('gmail','yahoo','hotmail','fcbk','aol');
				for(i=0;i<ims.length;i++){
					temp=getObject(ims[i]).value;
					if(temp!='' && (validate(temp,11) || temp.strlen>15)){
						createMessageBox('Error!! check '+ims[i]+' nick.','doNothing',false);
						return -1;
					}
					this.contacts.ims.ims[i]=(temp==undefined || temp=='undefined')?'':temp;
				}
					
				ims=getObject('inputs').childNodes.length;
				for(i=1;i<ims+1;i++){
					temp=getObject('name'+i).value;
					if(temp!='' && (validate(temp,11) || temp.strlen>15)){
						createMessageBox('Error!! check social name('+temp+').','doNothing',false);
						return -1;
					}
					this.contacts.ims.otitle[i-1]=(temp==undefined || temp=='undefined')?'':temp;
					temp=getObject('id'+i).value; 
					if(temp!='' && (validate(temp,11) || temp.strlen>15)){
						createMessageBox('Error!! check social('+this.contacts.ims.otitle[i-1]+') nick.','doNothing',false);
						return -1;
					}
					this.contacts.ims.oids[i-1]=(temp==undefined || temp=='undefined')?'':temp;
				}
			break;
		}
	},
   
	addOneMore: function (){
	var paro=getObject('inputs');
	var count=paro.childNodes.length;
	if(count==3) return;
	count++;
	var shtml="<input type='text' name='mob1' id='name"+count+"' size='13' value=''>&nbsp;&nbsp;<input type='text' name='mob1' id='id"+count+"' size='13' value=''><br />";
		var temp=document.createElement('span');
		temp.innerHTML=shtml;
		paro.appendChild(temp);
	},
   
	postContact: function (){
		//we have all the info the user wants so fire up e dbase
		var form=document.forms['addingcontact'];
		httpRequest=makeRequest();
		
		this.collectTabInfo(selTab);
		//the post values are not being sent with the POST request, so lets see if by  serializing them they will be sent
		var params=this.formatData();
		httpRequest.onreadystatechange = function() {results(httpRequest);};
		httpRequest.open("POST", 'seamless.php', true);
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	    httpRequest.send(params);
	},
   
	formatData: function (){
		//this is a big one!! we have to format the data to look like its from the input fields of a form.
		//we gonna use the array method of parsing data
		var params='';
		var temp=getObject('snameid').value;
		if(validate(temp,7)==false ||  validate(temp,0)==false || temp.strlen>20){
			createMessageBox('Error!! check surname.','doNothing',false);
			return -1;
		}else params+='surname='+encodeURIComponent(temp);
		
		temp=getObject('fnameid').value;
		if(validate(temp,7)==false || validate(temp,0)==false || temp.strlen>20){
			createMessageBox('Error!! check first name.','doNothing',false);
			return -1;
		}else params+='&fname='+encodeURIComponent(temp);
		
		temp=getObject('onamesid').value;
		if(temp!='' && (validate(temp,7)==false || temp.strlen>20)){
			createMessageBox('Error!! check other names.','doNothing',false);
			return -1;
		}else params+='&onames='+encodeURIComponent(temp);
		
		params+='&flag='+encodeURIComponent('postcontact');
		params+='&address='+encodeURIComponent(this.contacts.address);
		temp=document.getElementsByName('whose'); 
		temp=(temp[0].checked)?temp[0].value:temp[1].value;
		params+='&owner='+encodeURIComponent(temp);
		temp=this.contacts.tels.mobile;for(i=0;i<temp.length;i++) params+='&tmobile['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.tels.office;for(i=0;i<temp.length;i++) params+='&toffice['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.tels.home;for(i=0;i<temp.length;i++) params+='&thome['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.emails.personal;for(i=0;i<temp.length;i++) params+='&epersonal['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.emails.office;for(i=0;i<temp.length;i++) params+='&eoffice['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.emails;
		params+='&website[0]='+encodeURIComponent(temp.ppage);params+='&website[1]='+encodeURIComponent(temp.opage);
		params+='&website[2]='+encodeURIComponent(temp.blog);
		temp=this.contacts.ims.ims;for(i=0;i<temp.length;i++) params+='&ims['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.ims.otitle;for(i=0;i<temp.length;i++) params+='&nims['+i+']='+encodeURIComponent(temp[i]);
		temp=this.contacts.ims.oids;for(i=0;i<temp.length;i++) params+='&iims['+i+']='+encodeURIComponent(temp[i]);
		return params;
	},
   
	results: function (data){
	//we have the month selected in qst, so delete the 
		if(data.readyState==4){
			if(data.status==200 || data.status==304){
				var temp=getObject('errmessageid');
				temp.innerHTML=data.responseText;
			}else{
			}
		}
	},
   
	getContacts: function (id){
	//if id>9 we fetching types of contacts, if its 0 or 1 we getting view as
		if(id>9){
			//get new types
			curType=id-10;
		}
		else{
			//change view type
			curView=(id==0)?'list':'cards';
		}
		var stand='view='+encodeURIComponent(curView)+'&which='+encodeURIComponent(curType)+'&flag='+encodeURIComponent('getContacts');
		var params=stand+'&cont='+encodeURIComponent('content');
		httpRequest=makeRequest();
		httpRequest.onreadystatechange = function() {updateContent(httpRequest);};
		httpRequest.open("POST", 'seamless.php?page=contacts', true);
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	    httpRequest.send(params);
	},
   
	recreateLinks: function (id, type){
	var temp=new Array('telephones','emails','sites n blogs','messengers','addresses');
	var sublinks="<div class='sublinks'>all: ";
		for(i=0;i<temp.length;i++){
			if(id==i) sublinks+="<span>"+temp[i]+"</span>";
			else sublinks+="<a href='javascript:;' onClick='getContacts(1"+i+");'>"+temp[i]+"</a>";
		}
		sublinks+="</div>";
	
		temp=new Array('as list','as cards');
		sublinks+="<div class='sublinks' style='margin-bottom: 3px;'>view: ";
		for(i=0;i<temp.length;i++){
			if(temp[i]=="as "+type) sublinks+="<span>"+temp[i]+"</span>";
			else sublinks+="<a href='javascript:;' onClick='getContacts("+i+");'>"+temp[i]+"</a>";
		}
		sublinks+="</div>";
	
		var temp=getObject('all_sublinks');
		temp.innerHTML=sublinks;
	},
   
	updateContent: function (data){
		if(data.readyState==4){
			if(data.status==200 || data.status==304){
				var temp=getObject('bone');
				temp.innerHTML=data.responseText;
				this.recreateLinks(curType, curView);
			}else{
			}
		}
	}
}