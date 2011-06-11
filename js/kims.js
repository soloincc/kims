var Main = {
   title: 'kims personal page'
}

var Kims = {
   setAndSubmit: function(form,value){
      getObject('flagid').value=value;
      form.submit();
   },
   
   init: function(){
      if(paged=='contacts'){
         var tabs=new Array('tel. nos','emails','address','others');
         Contacts.generateTabs(tabs);
      }
   },
   
   getVariable: function(name, queryStr){
      //it gets a string as the variables passed in the location and returns a variable by the specific name
      queryStr=unescape(queryStr)		//make it a proper string
      queryStr=queryStr.replace("+"," ").replace("+"," ")	//remove the +'s
      if(queryStr.length != 0) {
         splitArray = queryStr.split("&")	//convert it to an array
         for (i=0; i<splitArray.length; i++) {
            var splits=splitArray[i].split("=");
            if(splits[0]==name) return splits[1];
         }
      }
      return undefined;
   },
   
   ajaxRequest: function(url, processor, type, params){
      httpRequest=makeRequest(type);
      httpRequest.onreadystatechange = function(){eval(processor)};
      httpRequest.open("POST", url, true);
      httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
       httpRequest.send(params);
   }
}

var paged = Kims.getVariable('page',parent.document.location.search.substring(1));