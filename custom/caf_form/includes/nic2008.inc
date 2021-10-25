<?php
function search_nic_code($ajax){
	 //return  drupal_get_form('ind_pensioner_display_pension_amount',$penid); 
	 if ($ajax) {
     // Required includes for ctools to work:
    ctools_include('ajax');
    ctools_include('modal');
	ctools_modal_add_js();
     $form_state = array(
       'ajax' => TRUE,
       'title' => t(''),
     );
	 
	  //$id=9;
	  //$form_state['build_info']['args'] = array($penid , $id);
	  //$form_state['build_info']['args'] = array($id);
      $output = ctools_modal_form_wrapper('nic_2008_search_inspector', $form_state);
	  
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    
	print ajax_render($output);
    drupal_exit();
     
   } else {
     return drupal_get_form('nic_2008_search_inspector');
   }
   }
   
function nic_2008_search_inspector($form, &$form_state) {	
  
  
  
  $form = array();
  $form['nic2008']['serch_main_activity_nm'] = array
        (
		'#title' => ' Main Activity  Name  ',
	    '#size'=>t('50'),	
	    '#type' => 'textfield',
		//'#required' => TRUE,
		 '#prefix' => '<table><tr><td  colspan="2">',
         '#suffix' => '</td>',
	    
     
	   // '#element_validate' => array('EMONE_ADDRESS_CHECKING_validate'),
		
        );	  
		$form['nic2008']['acti_div_search_btn'] = array(
       
	   
	   '#prefix' => '<td  colspan="1">',
        '#suffix' => '</td></tr></table>',
		
		'#type' => 'button',
        //'#disabled' => TRUE, 
        '#default_value' => 'Search by main activity name',
        '#ajax' => array(
        'callback' => 'factori_activity_div_search_admin',
        'wrapper' => 'factori_mandivshow',
        'method' => 'html',
        'effect' => 'fade'
    )

   );  
		  
	
$form['nic2008']['show_act_div'] = array(
       
	   
	   '#prefix' => '<div id="factori_mandivshow">',
        '#suffix' => '</div>',
		
		
     ); 
	 
	  return $form;	

}

function factori_activity_div_search_admin($form, $form_state){

	
	$products=trim($form_state['values']['serch_main_activity_nm']);

      if(!$products)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter  product/service  name <b>    </font>";
	 } 
	 
	 $val="a".trim($products);
		if(stripos($val,"~") >0  || stripos($val,"!") >0 || stripos($val,"@")>0 || stripos($val,"<")>0 || stripos($val,">")>0 || stripos($val,"'")>0 || stripos($val,"$")>0 || stripos($val,"#")>0 || stripos($val,"%")>0 || stripos($val,"^")>0 || stripos($val,"&")>0 || stripos($val,"*")>0){
		
		drupal_get_messages(error);
	    return "<font color='#FF3333'><b> Main Activity Name  contain illegal character <b>    </font>";
       
           
       
		    
	   }	


        $show_details_query = db_select('nic_2008_code_details', 'a');
        
	   $show_details_query->fields('a', array('sub_class_code','sub_class_name','division','division_name'));
      
	  $show_details_query->condition('sub_class_name',trim($products),'='); 
        $query_ent=$show_details_query->execute();

      if($query_ent->rowCount()== 0){
	    $search_string=array();
		$splitchar=" ";	 
		$search_string = preg_split("/[\s,-]+/", $products)    ; 
		
		 for ($i = 0 ; $i < count($search_string); $i++){




        $show_details_query = db_select('nic_2008_code_details', 'a');
        
	   $show_details_query->fields('a', array('sub_class_code','sub_class_name','division','division_name'));
      
	
		
	    $show_details_query->condition('sub_class_name',"%".trim($search_string[$i])."%",'LIKE'); 
		$query_ent=$show_details_query->execute();
		
		  if ($query_ent->rowCount() > 0) {
           break;
        }
      }
		
	  }


 $output = "<table style='width: 100%; border-collapse: collapse; '>
	 
	    <tr bgcolor=\"#CCCCCC\"> 
        <td ><b>DIVISION CODE</b></td>
         <td><b> DIVISION NAME</b></td>
	      <td><b>MAIN ACTIVITY CODE(NIC 2008 )</b></td>
          <td> <b> MAIN ACTIVITY NAME </b></td>
		 
		</tr>
		
		";
	
	       $i=0;
		
	     if($query_ent->rowCount()>0) 
              { 
		foreach($query_ent as $squan) {
			$i++;

                       $div_id=$squan->division;
		               $div_desc=$squan->division_name;
                      $sub_class_code=$squan->sub_class_code;
		               $sub_class_name=$squan->sub_class_name;
             
       if($i%2==0){
		       $output .= "<tr bgcolor=\"#ecebbd\">";
			    $tr="<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output .= "<tr bgcolor=\"#FFFFFF\">";
				$tr="<tr bgcolor=\"#BDB76B\">";
				}
			
		      $output .= "<td colspan=\"1\" >".$div_id."</td>";
              $output .= "<td colspan=\"1\">".$div_desc."</td>";
              $output .= "<td colspan=\"1\" >".$sub_class_code."</td>";
              $output .= "<td colspan=\"1\">".$sub_class_name."</td></tr>";
 }
	
	
	
      $output .= "</table>"; 
		  
			
		   drupal_get_messages(error);
		   
		   
		  return $output;

}
else
	{
		 drupal_get_messages(error);
		 return " <font color='#FF3333'><b> NO RESULT   </b>    </font> ";	
	      
		
	}

}
?>