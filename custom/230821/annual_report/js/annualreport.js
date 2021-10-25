 function annualReport(code){


	//alert('sssss'+code);
	var curYear= new Date().getFullYear();
	//alert(curYear);
	
	/**/

    if (code === "CALENDAR") {
                        var ReportYear = parseInt(curYear) - 1;
                        var FromDate = ReportYear + "-01-01";
                        var ToDate = ReportYear + "-12-31";
                        //$("#Year").text(ReportYear);
                        jQuery("#edit-from").val(FromDate);
                        jQuery("#edit-to").val(ToDate);
                    } else {
                        var ReportYear = parseInt(curYear) - 1 + "-" + curYear;
                        var FromDate = (parseInt(curYear) - 1).toString() + "-04-01";
                        var ToDate = curYear + "-03-31";
                       // $("#Year").text(ReportYear);
                        jQuery("#edit-from").val(FromDate);
                        jQuery("#edit-to").val(ToDate);
                    }


}


function trim(str)
{
	return str.replace(/^\s+|\s+$/g,'');
}

function addIA(code ){
	 //alert("ssss");
	
	if(code=='G'){
	 var gfone=Number(jQuery("#edit-gfone").val());
	
	 var gftwo=Number(jQuery("#edit-gftwo").val());
	 var gfthree=Number(jQuery("#edit-gfthree").val());
	 var gffour=Number(jQuery("#edit-gffour").val());

	 var gffive=Number(jQuery("#edit-gffive").val());
	 var gfsix=Number(jQuery("#edit-gfsix").val());
	 var gfseven=Number(jQuery("#edit-gfseven").val());
	
	   
	/*if(gfone < 1 || gfone==''|| isNaN(gfone) ){
	 gfone=0;
	
	}
	elseif(gftwo < 1 || gftwo=='' || isNaN(gftwo)){
	 gftwo=0;
	
	}
	 */
 
  var gftotal=gfone  + gftwo +  gfthree + gffour + gffive + gfsix + gfseven; 
  // alert("ssss"+Gfone);
  //document.getElementById("edit-Gfeight").value=Gfone  ; 
 
  //alert("ssss"+gfone);
   jQuery("#edit-gfeight").val(gftotal);

     }
    
else if(code=='H') 
   {
	 var gfone=Number(jQuery("#edit-hfone").val());
	
	 var gftwo=Number(jQuery("#edit-hftwo").val());
	 var gfthree=Number(jQuery("#edit-hfthree").val());
	 var gffour=Number(jQuery("#edit-hffour").val());

	 var gffive=Number(jQuery("#edit-hffive").val());
	 var gfsix=Number(jQuery("#edit-hfsix").val());
	 var gfseven=Number(jQuery("#edit-hfseven").val());
	
	   
	/*
	elseif(Gfseven < 1 || Gfseven=='' || isNaN(Gfseven)){
	 Gfseven=0;
	
	} */
 
 var gftotal=gfone  + gftwo +  gfthree + gffour + gffive + gfsix + gfseven; 
  // alert("ssss"+Gfone);
  //document.getElementById("edit-Gfeight").value=Gfone  ; 
 
  //alert("ssss"+gfone);
   jQuery("#edit-hfeight").val(gftotal);

     }

     else if(code=='M') 
   {
	 var gfone=Number(jQuery("#edit-mahfone").val());
	
	 var gftwo=Number(jQuery("#edit-mahftwo").val());
	 var gfthree=Number(jQuery("#edit-mahfthree").val());
	 var gffour=Number(jQuery("#edit-mahffour").val());

	 var gffive=Number(jQuery("#edit-mahffive").val());
	 var gfsix=Number(jQuery("#edit-mahfsix").val());
	 var gfseven=Number(jQuery("#edit-mahfseven").val());
	
	   
	/* */
 
 var gftotal=gfone  + gftwo +  gfthree + gffour + gffive + gfsix + gfseven; 
  // alert("ssss"+Gfone);
  //document.getElementById("edit-Gfeight").value=Gfone  ; 
 
  //alert("ssss"+gfone);
   jQuery("#edit-mahfeight").val(gftotal);

     }
	
	 
	
}

function addIB(code ){
	// alert("BBBB");
	
	if(code=='G'){
	 var gfone=Number(jQuery("#edit-gfoneb").val());
	
	 var gftwo=Number(jQuery("#edit-gftwob").val());
	 var gfthree=Number(jQuery("#edit-gfthreeb").val());
	 var gffour=Number(jQuery("#edit-gffourb").val());

	 var gffive=Number(jQuery("#edit-gffiveb").val());
	 var gfsix=Number(jQuery("#edit-gfsixb").val());
	 var gfseven=Number(jQuery("#edit-gfsevenb").val());
	
	   
	/*if(gfone < 1 || gfone==''|| isNaN(gfone) ){
	 gfone=0;
	
	}
	elseif(gftwo < 1 || gftwo=='' || isNaN(gftwo)){
	 gftwo=0;
	
	}
	 */
 
  var gftotal=gfone  + gftwo +  gfthree + gffour + gffive + gfsix + gfseven; 
   //alert("ssss"+gftotal);
  //document.getElementById("edit-Gfeight").value=Gfone  ; 
 
  //alert("ssss"+gfone);
   jQuery("#edit-gfeightddb").val(gftotal);

     }
    
else if(code=='H') 
   {
	 var gfone=Number(jQuery("#edit-hfoneb").val());
	
	 var gftwo=Number(jQuery("#edit-hftwob").val());
	 var gfthree=Number(jQuery("#edit-hfthreeb").val());
	 var gffour=Number(jQuery("#edit-hffourb").val());

	 var gffive=Number(jQuery("#edit-hffiveb").val());
	 var gfsix=Number(jQuery("#edit-hfsixb").val());
	 var gfseven=Number(jQuery("#edit-hfsevenb").val());
	
	   
	/*
	elseif(Gfseven < 1 || Gfseven=='' || isNaN(Gfseven)){
	 Gfseven=0;
	
	} */
 
 var gftotal=gfone  + gftwo +  gfthree + gffour + gffive + gfsix + gfseven; 
  // alert("ssss"+Gfone);
  //document.getElementById("edit-Gfeight").value=Gfone  ; 
 
  //alert("ssss"+gfone);
   jQuery("#edit-hfeightb").val(gftotal);

     }

     else if(code=='M') 
   {
	 var gfone=Number(jQuery("#edit-mahfoneb").val());
	
	 var gftwo=Number(jQuery("#edit-mahftwob").val());
	 var gfthree=Number(jQuery("#edit-mahfthreeb").val());
	 var gffour=Number(jQuery("#edit-mahffourb").val());

	 var gffive=Number(jQuery("#edit-mahffiveb").val());
	 var gfsix=Number(jQuery("#edit-mahfsixb").val());
	 var gfseven=Number(jQuery("#edit-mahfsevenb").val());
	
	   
	/* */
 
 var gftotal=gfone  + gftwo +  gfthree + gffour + gffive + gfsix + gfseven; 
  // alert("ssss"+Gfone);
  //document.getElementById("edit-Gfeight").value=Gfone  ; 
 
  //alert("ssss"+gfone);
   jQuery("#edit-mahfeightb").val(gftotal);

     }
	
	 
	
}


function frequenC(code ){
	
	 var col2val=Number(jQuery("#edit-col2val").val());
	 var col3val=Number(jQuery("#edit-col3val").val());
	 var col4val=Number(jQuery("#edit-col4val").val());
	 var col5val=Number(jQuery("#edit-col5val").val());
	 

	
	   if(code=='R'){
	
 
   var regtotal=col2val  + col4val;
   jQuery("#edit-col6val").val(regtotal);
    }
   else if(code=='U'){
   var unregtotal=col3val  + col5val;
   jQuery("#edit-col7val").val(unregtotal);

   }
   
  
  

     }


 function addVP( ){


     var misval=Number(jQuery("#edit-misval").val());
	 var pwdval=Number(jQuery("#edit-pwdval").val());
	 var mbaval=Number(jQuery("#edit-mbaval").val());
	 var carval=Number(jQuery("#edit-carval").val());
	 var cival=Number(jQuery("#edit-cival").val());

	 var drival=Number(jQuery("#edit-drival").val());
	 var balhval=Number(jQuery("#edit-balhval").val());
	 var oshhval=Number(jQuery("#edit-oshhval").val());
	 var faopval=Number(jQuery("#edit-faopval").val());
	 var frolval=Number(jQuery("#edit-frolval").val());


	
	 var cold12val=Number(jQuery("#edit-cold12val").val());
	 var cold13val=Number(jQuery("#edit-cold13val").val());
	 var cold14val=Number(jQuery("#edit-cold14val").val());
	 var cold15val=Number(jQuery("#edit-cold15val").val());
	 var cold16val=Number(jQuery("#edit-cold16val").val());

	 

	
	   
 
   var regtotal= misval + pwdval + mbaval + carval + cival + drival + balhval + oshhval + faopval + frolval 
   + cold12val  + cold13val + cold14val + cold15val + cold16val;
   jQuery("#edit-cold17val").val(regtotal);
    
   
  
  

     }    

