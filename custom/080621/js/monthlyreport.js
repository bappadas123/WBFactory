 
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



   
  
  

   

