<?php

function annual_report_step12( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	     $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	 
	
	      
	
	
	
		  $step12a_query = db_select('labour_factory_statcell_annual_report_attach_construct_t1', 'a');
       
        $step12a_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step12a_query->fields('a',array('unit_visited' ,
  'visit_paid' ,
  'violation' ,
  'accident' ,
  'fatal' ,
  'serious' ,
  'connection_accident' ,
  'complaints' ,
  'connection_complaints' ,
  'prosecution'));
        $step12a_query_result = $step12a_query->execute(); 
		 
		$result_step2a=$step12a_query_result->fetchAssoc();
		$unit_visited=$result_step2a['unit_visited'];
		$visit_paid=$result_step2a['visit_paid'];
        $violation=$result_step2a['violation'];
      
        $accident=$result_step2a['accident'];
		
		$fatal=$result_step2a['fatal'];
		$serious=$result_step2a['serious'];
	    $connection_accident=$result_step2a['connection_accident'];
	    $complaints=$result_step2a['complaints'];
	    $connection_complaints=$result_step2a['connection_complaints'];
	    $prosecution=$result_step2a['prosecution'];

		
    
	 $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
       $inspector_name=get_name($inspector_id);
	    $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
      $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));   
	
	
	// Part 4
		
	      $form['step12Afield'] = array(
          '#title' => t('<b>  Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.' </b>'),
         '#type' => 'fieldset',
          
          ); 
           $form['step12Afield']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );

		
     	
$form['step12Afield']['colA1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>A. Construction Works Details</b></div><div class="form-group row"><div class="col-sm-6" >', 
		     

		          '#suffix'=>'</div>',

		            '#type' => 'textfield',
		              '#size' => 1,

		                '#title' =>"1.Number of units visited",

                     '#default_value' =>$unit_visited
	   
	   
           );


               
    $form['step12Afield']['colA2'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"2. Number of visits paid",
		        '#suffix'=>'</div>',
		          '#default_value' =>$visit_paid
	   
	   
           ); 

      $form['step12Afield']['colA3'] = array
              (
		       '#prefix' => ' <div class="col-sm-6" >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"3. Total number of violations observed",
	   
	         '#default_value' =>$violation
           ); 



$form['step12Afield']['colA4'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		        
		           '#title' =>"4. No of Accidents ",
                '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
	       '#default_value' =>$accident
	   
           );
           $form['step12Afield']['colA5'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		      
		        '#title' =>"a)  Fatal.",
               '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
	    '#default_value' =>$fatal
	   
           );
              
$form['step12Afield']['colA6'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		        
		           '#title' =>"b)  Serious.",
                '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
		           '#default_value' =>$serious
	   
	   
           );
          

           
             
             
 $form['step12Afield']['colA7'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		       
		         '#title' =>"5.No of visits paid in connection with accidents",
               
               '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
		           '#default_value' =>$connection_accident
	   
	   
           );


           $form['step12Afield']['colA8'] = array
              (
		       '#prefix' => ' <div class="col-sm-6" >', 
		       
		         '#title' =>"6. No of complaints received",
               
               '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
		               '#default_value' =>$complaints
	   
	   
           );

           $form['step12Afield']['colA9'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		       
		         '#title' =>"7. No of visits paid in connection with complaints",
               
               '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
		             '#default_value' =>$connection_complaints
	   
	   
           );

           $form['step12Afield']['colA10'] = array
              (
		       '#prefix' => '<div class="col-sm-6" >', 
		       
		         '#title' =>"8. No. of prosecution launched",
               
               '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
		            '#default_value' =>$prosecution
	   
	   
           );
$form['step12Afield']['submit_button_2A']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" class="col-sm-12"   >',
                                                                 '#suffix'=>'</div></div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save Construction Works Details '),
																
																'#submit' => array('step12_parta_save'),
																 
																);
              






           $form['step12Bfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

	


     	


               



             

             $form['step12Bfield']['col1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>B.Construction Works Case Details</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th>', 
		       '#markup'=>'<b> Case No  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step12Bfield']['col2'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Violation </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step12Bfield']['col3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Court  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step12Bfield']['col4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Remarks </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

     $form['step12Bfield']['colB11val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		      '#type' => 'textfield',
                '#size' => 10,
           
		        '#suffix'=>'</td>',
	   
	   
           ); 
           $form['step12Bfield']['colB12val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td>',
	   
	   
           );
           $form['step12Bfield']['colB13val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td>',
	   
	   
           );
           $form['step12Bfield']['colB14val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           );
           	$form['step12Bfield']['submit_button_12b']					= array(
																 
                                                              '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																	'#type' => 'button',
		                                                           '#event' => 'click',

																 '#default_value' => 'ADD CW CASE  DETAILS  ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step12b_data',
                                                              'wrapper' => 'data12b_show',
                                                                'method' => 'html',
                                                                     'effect' => 'fade'
                                                               )
																);


   $output1='';
      if(trim($filenumber)){
      $query_tab_12_b=db_query('select  *  from labour_factory_statcell_annual_report_attach_construct_t2 where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_12_b->rowCount() > 0) 
              { 
      $output1 = "<div class='table-responsive'>
			   <table class='table table-striped table-bordered table-responsive add-employee-table-view'><thead>
	    <tr > <th >SL.NO</th>
      
       <th > Case No. </th>
	    <th >Violation </th>
       
		 <th >Court</th>

		 <th >Remarks</th>
       
		
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_12_b as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $case_no=$squan->case_no;
			  $violation=$squan->violation;
			  $court=$squan->court;
              $remarks=$squan->remarks;
              
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab12b-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "";
				 }
				else
				{
				$output1 .= "";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$case_no."</td>";
			    $output1.= "<td>".$violation."</td>";
                $output1.= "<td>".$court."</td>";
                $output1.= "<td>".$remarks."</td>";
               
			
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table></div>"; 
			  
			

	
	   }
	}
	 $form['step12Bfield']['data12b'] = array(
	 	'#prefix' => '<div align="left" id="data12b_show">'.$output1,
		'#suffix' => '</div>',
       
	);


       $step12_c_query = db_select('labour_factory_statcell_annual_report_attach_maternity_t1', 'a');
       
        $step12_c_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
        $step12_c_query->fields('a',array('no_act_and_rules_1_a',
  'no_non_maintenance_muster_roll_1_b',
  'no_imp_maintenance_1_c',
  'maternity_benefit_1_d' ,
  'others_1_e' ,
  'regd_number_2' ,
  'reg_investigate_2' ,
  'reg_violation_2' ,
  'reg_action_2' ,
  'reg_remarks_2' ,
  'unreg_number_2' ,
  'unreg_investigate_2' ,
  'unreg_violation_2' ,
  'unreg_action_2' ,
  'unreg_remarks_2' ,
  'case_pending_at_beginning_4_a' ,
  'case_disposed_4_b' ,
  'case_pending_at_end_4_c' ));
        $step12_c_query_result = $step12_c_query->execute(); 
		
		$result_step12c=$step12_c_query_result->fetchAssoc();

		$no_act_and_rules_1_a=$result_step12c['no_act_and_rules_1_a'];
        $no_non_maintenance_muster_roll_1_b=$result_step12c['no_non_maintenance_muster_roll_1_b'];
        $no_imp_maintenance_1_c=$result_step12c['no_imp_maintenance_1_c'];
        $maternity_benefit_1_d=$result_step12c['maternity_benefit_1_d'];
		
		$others_1_e=$result_step12c['others_1_e'];
		$regd_number_2=$result_step12c['regd_number_2'];

		$reg_investigate_2=$result_step12c['reg_investigate_2'];

		$reg_violation_2=$result_step12c['reg_violation_2'];

		$reg_action_2=$result_step12c['reg_action_2'];

		$reg_remarks_2=$result_step12c['reg_remarks_2'];




		$unreg_number_2=$result_step12c['unreg_number_2'];

		$unreg_investigate_2=$result_step12c['unreg_investigate_2'];

		$unreg_violation_2=$result_step12c['unreg_violation_2'];

		$unreg_action_2=$result_step12c['unreg_action_2'];

		$unreg_remarks_2=$result_step12c['unreg_remarks_2'];


		$case_pending_at_beginning_4_a=$result_step12c['case_pending_at_beginning_4_a'];

		$case_disposed_4_b=$result_step12c['case_disposed_4_b'];

		$case_pending_at_end_4_c=$result_step12c['case_pending_at_end_4_c'];

// Part C

             $form['step12Cfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

$form['step12Cfield']['head1'] = array
              (
			  	'#title' => t('<b>  Maternity Benefits Act Rules </b>'),
		       '#prefix' => '<div class="table-panel-header"><b>1.No. of violations in respect of</b></div><div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<b>   </b>',
				
		          '#suffix'=>'</div></div>',
	   
	   
           );
          $form['step12Cfield']['colC1'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-md-6 col-sm-12 col-xs-12">', 
		     

		          '#suffix'=>'</div>',

		            '#type' => 'textfield',
		              '#size' => 5,

		                '#title' =>" a)	Display of the Abstract of the Act and the Rules",

		                 '#default_value' =>$no_act_and_rules_1_a


	   
	   
           );


               
    $form['step12Cfield']['colC2'] = array
              (
		       '#prefix' => '<div class="col-md-6 col-sm-12 col-xs-12">', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"b)	Non-maintenance of muster roll",
		        '#suffix'=>'</div>',
		         '#default_value' =>$no_non_maintenance_muster_roll_1_b
	   
	   
           ); 

      $form['step12Cfield']['colC3'] = array
              (
		       '#prefix' => ' <div class="col-md-6 col-sm-12 col-xs-12">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"c)	Improper maintenance of muster roll",
		          '#default_value' =>$no_imp_maintenance_1_c
	   
	   
           ); 


              
$form['step12Cfield']['colC4'] = array
              (
		       '#prefix' => '<div class="col-md-6 col-sm-12 col-xs-12">', 
		        
		           '#title' =>"d)	Payment of maternity benefits",
                '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',

		           '#default_value' =>$maternity_benefit_1_d
	   
	   
           );
           $form['step12Cfield']['colC5'] = array
              (
		       '#prefix' => '<div class="col-md-6 col-sm-12 col-xs-12">', 
		      
		        '#title' =>"e)Others",
               '#type' => 'textfield',
                '#size' => 5,
		        '#suffix'=>'</div></div>',
		          '#default_value' =>$others_1_e
	   
	   
           );

           
             
             
 $form['step12Cfield']['head2'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 

		          '#suffix'=>'</div></div>',
	   
	   
           );




           $form['step12Cfield']['colD1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>2. No. of compaints settled after investigation</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b>   </b>',


	   
	   
           );
               

             $form['step12Cfield']['colD2'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Number  </b>',


	   
	   
           );  

            $form['step12Cfield']['colD3'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Investigated  </b>',


	   
	   
           );      
 $form['step12Cfield']['colD4'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Violation observed  </b>',


	   
	   
           ); 

           $form['step12Cfield']['colD5'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Action taken  </b>',


	   
	   
           ); 

           $form['step12Cfield']['colD6'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th></tr></thead>',

		            
		       '#markup'=>'<b>Remarks  </b>',


	   
	   
           ); 

           $form['step12Cfield']['colD1val'] = array
              (
		       '#prefix' => '<tr> <th >', 
		      // '#type' => 'textfield',
              //  '#size' => 5,
             '#markup'=>'Regd. factories</b>',
		        '#suffix'=>'</th>',
		            
	   
	   
           ); 


          $form['step12Cfield']['colD2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
            
		        '#suffix'=>'</td>',
		        '#default_value' =>$regd_number_2
		      
	   
	   
           ); 

           $form['step12Cfield']['colD3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td>',
		           '#default_value' =>$reg_investigate_2
		          
	   
	   
           ); 
          $form['step12Cfield']['colD4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		         '#default_value' =>$reg_violation_2
		        
	   
	   
           ); 
           $form['step12Cfield']['colD5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		          '#default_value' =>$reg_action_2
		         
	   
	   
           ); 
           $form['step12Cfield']['colD6val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
                   '#default_value' =>$reg_remarks_2,
		          '#suffix'=>'</td></tr>',
	   
	   
           );
           $form['step12Cfield']['colD11val'] = array
              (
		       '#prefix' => '<tr> <th  >', 
		      // '#type' => 'textfield',
              //  '#size' => 5,
             '#markup'=>'Un-regd. factories</b>',
		        '#suffix'=>'</th>',
	   
	   
           ); 


          $form['step12Cfield']['colD21val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
            
		        '#suffix'=>'</td>',
		         '#default_value' =>$unreg_number_2,
	   
	   
           ); 

           $form['step12Cfield']['colD31val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td>',
		           '#default_value' =>$unreg_investigate_2,
	   
	   
           ); 
          $form['step12Cfield']['colD41val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		          '#default_value' =>$unreg_violation_2,
	   
	   
           ); 
           $form['step12Cfield']['colD51val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		          '#default_value' =>$unreg_action_2,
	   
	   
           ); 
           $form['step12Cfield']['colD61val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
		          '#suffix'=>'</td></tr></table></div>',
		                 '#default_value' =>$unreg_remarks_2,
	   
	   
           );




       
    
       


           $form['step12Cfield']['colF1'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-7">', 
		     

		          '#suffix'=>'</div>',

		            '#type' => 'textfield',
		              '#size' => 5,

		                '#title' =>"4.	a)	No. of case pending at the beginning of the year",
		                   '#default_value' =>$case_pending_at_beginning_4_a,


	   
	   
           );


               
    $form['step12Cfield']['colF2'] = array
              (
		       '#prefix' => '<div class="col-sm-7">', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"	b)	No. of case in disposed off during the year",
		        '#suffix'=>'</div>',
		          '#default_value' =>$case_disposed_4_b,
	   
	   
           ); 

      $form['step12Cfield']['colF3'] = array
              (
		       '#prefix' => ' <div class="col-sm-7">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"	c)	No. of case pending at the end of the year",
		          '#default_value' =>$case_pending_at_end_4_c,
	   
	   
           ); 


           $form['step12Cfield']['submit_button_12c']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" class="col-sm-12" >',
                                                                 '#suffix'=>'</div></div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save Maternity benefit Details '),
																
																'#submit' => array('annual_report_step12c_save'),
																 
																);


 $form['step12Cfield']['colE1'] = array
              (
		       '#prefix' => '<div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> 3.Name of the factory					
  </b>',


	   
	   
           );
               

             $form['step12Cfield']['colE2'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Section-Rules violated  </b>',


	   
	   
           );  

            $form['step12Cfield']['colE3'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Case No.  </b>',


	   
	   
           );      
 $form['step12Cfield']['colE4'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Amount of fines posted  </b>',


	   
	   
           ); 

           $form['step12Cfield']['colE5'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th></tr></thead>',

		            
		       '#markup'=>'<b> Remarks if any  </b>',


	   
	   
           ); 

           

           $form['step12Cfield']['colE1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textarea',
		          
                '#rows' => 2,
                 '#cols' => 2,
            
		        '#suffix'=>'</td>',
	   
	   
           ); 


          $form['step12Cfield']['colE2val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textarea',
		          
                '#rows' => 5,
                 '#cols' => 5,
            
		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step12Cfield']['colE3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           
		        '#suffix'=>'</td>',
	   
	   
           ); 
          $form['step12Cfield']['colE4val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textfield',
                '#size' => 5,
             
		        '#suffix'=>'</td>',
	   
	   
           ); 
           $form['step12Cfield']['colE5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,
             
		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           ); 
          

      
            $form['step12Cfield']['ajax_add'] = array(
	
	 
	   '#prefix' => '<div class="row"><div class="col-sm-12" style="text-align:center;" >',
        '#suffix' => '</div></div>',
	   '#type' => 'button',
		'#event' => 'click',
	
		 //  '#attributes' => array('class' => array('estab-btn-pad')),
        //'#disabled' => TRUE, 
        '#default_value' => 'Add  MB Case Details ',
        '#ajax' => array(
        'callback' => 'add_step12c_data',
        'wrapper' => 'data12c_show',
        'method' => 'html',
        'effect' => 'fade'
    )
		
    );

       $output2='';
      if(trim($filenumber)){
      $query_tab_12_c=db_query('select  *  from labour_factory_statcell_annual_report_attach_maternity_wages where  maternity_wages_id = :anid and maternity_wages_type = :mwt', array(':anid' => trim($filenumber) , ':mwt' => 'MATERNITY'));
      if($query_tab_12_c->rowCount() > 0) 
              { 
      $output2 = "<div class='table-responsive'>
			   <table class='table table-striped table-bordered table-responsive add-employee-table-view'><thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the factory. </th>
	    <th >Section-Rules violated </th>
       
		 <th >Case No.</th>

		 <th >Amount of fines posted</th>
       
		 <th >Remarks</th>

		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_12_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $maternity_wages_id = $squan->maternity_wages_id; 
	          $maternity_wages_type=$squan->maternity_wages_type;
			
              
            
              
			 // $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab12c-del/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output2 .= "";
				 }
				else
				{
				$output2 .= "";
				}
				$output2.= "<td>".$i."</td>"; 
				$output2.= "<td>".$squan->factory_name_3."</td>";
			    $output2.= "<td>".$squan->section_rules_3."</td>";
                $output2.= "<td>".$squan->case_number_3."</td>";
                $output2.= "<td>".$squan->amount_fine_3."</td>";
                 $output2.= "<td>".$squan->remarks_3."</td>";
               
			
				$output2.= "<td >".$del_preper."</td>";
			
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table></div>"; 
			  
			

	
	   }
	}
	 $form['step12Cfield']['data12c'] = array(
	 	'#prefix' => '<div align="left" id="data12c_show">'.$output2,
		'#suffix' => '</div>',
       
	);






$step12d_query = db_select('labour_factory_statcell_annual_report_attach_wages_t1', 'd');
       
        $step12d_query->condition('d.annual_inspection_id',trim($filenumber),'=');
      
		
        $step12d_query->fields('d',array('no_act_and_rules_1_a',
  'no_notice_dates_payment_1_b' ,
  'no_non_maintenance_wages_1_c' ,
  'no_imp_maintenance_wages_1_d' ,
  'no_recording_date_payment_1_e' ,
  'no_register_wages_1_f' ,
  'no_delayed_wages_1_g' ,
  'no_others_1_h' ,
  'regd_number_2' ,
  'reg_investigate_2' ,
  'reg_violation_2' ,
  'reg_action_2' ,
  'reg_remarks_2' ,
  'unreg_number_2',
  'unreg_investigate_2',
  'unreg_violation_2' ,
  'unreg_action_2',
  'unreg_remarks_2' ,
  'case_pending_at_beginning_3_a' ,
  'case_disposed_3_b',
  'case_pending_at_end_3_c' ,
  'factories_name_4_a' ,
  'application_filed_4_b' ,
  'person_involved_4_c' ,
  'wages_claimed_4_d' ,
  'deduction_claimed_4_e' ,
  'app_pending_at_beginning_4_f' ,
  'app_disposed_4_g',
  'app_pending_at_end_4_h' ));
        $step12d_query_result = $step12d_query->execute(); 
		 
		$result_step2d=$step12d_query_result->fetchAssoc();


 $form['step12Dfield'] = array(
          '#title' => t('<b>  Payment of wages  </b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

$form['step12Dfield']['head11'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<div class="table-panel-header"><b> Information relating to payment of Wages act & Rules  </b></div>',

		          '#suffix'=>'</div></div>',
	   
	   
           );

 $form['step12Dfield']['head223'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<div class="table-panel-header"><b> 1. No. of violations in respect of  </b></div>',

		          '#suffix'=>'</div></div>',
	   
	   
           );

          $form['step12Dfield']['colO1'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-6">', 
		     

		          '#suffix'=>'</div>',

		         '#type' => 'textfield',
                '#size' => 5,

		        '#title' =>" a)	Display of the Abstract of the Act and the Rules",
		        '#default_value' =>$result_step2d['no_act_and_rules_1_a']


	   
	   
           );


               
    $form['step12Dfield']['colO2'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"(b) Display of the notice of dates of payment",
		        '#suffix'=>'</div>',
	          '#default_value' =>$result_step2d['no_notice_dates_payment_1_b']
	   
           ); 

      $form['step12Dfield']['colO3'] = array
              (
		       '#prefix' => ' <div class="col-sm-6">', 
		      '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"(c) Non-maintenance of register of wages",
		          '#default_value' =>$result_step2d['no_non_maintenance_wages_1_c']
	   
	   
           ); 


              
$form['step12Dfield']['colO4'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		        
		           '#title' =>"(d) Improper maintenance of register of wages",
               '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</div>',
		            '#default_value' =>$result_step2d['no_imp_maintenance_wages_1_d']
	   
	   
           );
           $form['step12Dfield']['colO5'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		      
		        '#title' =>"(e) Irregularities in recording dates of payment",
               '#type' => 'textfield',
                '#size' => 5,
		        '#suffix'=>'</div>',
		      '#default_value' =>$result_step2d['no_recording_date_payment_1_e']
	   
	   
           );

            $form['step12Dfield']['colO6'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		      
		       '#type' => 'textfield',
                '#size' => 5,
		        '#suffix'=>'</div>',
	              '#title' =>"(f)Non-availability of register of wages",

	              '#default_value' =>$result_step2d['no_register_wages_1_f']
	   
           );

           $form['step12Dfield']['colO7'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		      
		        '#title' =>"(g) Delayed wages",
               '#type' => 'textfield',
                '#size' => 5,
		        '#suffix'=>'</div>',
		       '#default_value' =>$result_step2d['no_delayed_wages_1_g']
	   
	   
           );

            $form['step12Dfield']['colO8'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		      
		        '#title' =>"(h) Others",
              '#type' => 'textfield',
                '#size' => 5,
		        '#suffix'=>'</div></div>',
		         '#default_value' =>$result_step2d['no_others_1_h']
	   
	   
           );
             
             
 $form['step12Dfield']['head22'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<b>   </b>',

		          '#suffix'=>'</div></div>',
	   
	   
           );

           $form['step12Dfield']['colP1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>2. No. of complaints settled after investigation</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b>   </b>',


	   
	   
           );
               

             $form['step12Dfield']['colP2'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Number  </b>',


	   
	   
           );  

            $form['step12Dfield']['colP3'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Investigated  </b>',


	   
	   
           );      
 $form['step12Dfield']['colP4'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Violation observed  </b>',


	   
	   
           ); 

           $form['step12Dfield']['colP5'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Action taken  </b>',


	   
	   
           ); 

           $form['step12Dfield']['colP6'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th></tr></thead>',

		            
		       '#markup'=>'<b>Remarks  </b>',


	   
	   
           ); 

           $form['step12Dfield']['colP1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		      // '#type' => 'textfield',
              //  '#size' => 5,
             '#markup'=>'Regd. factories</b>',
		        '#suffix'=>'</td>',
	   
	   
           ); 


          $form['step12Dfield']['colP2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
            
		        '#suffix'=>'</td>',
		        
		       '#default_value' =>$result_step2d['regd_number_2']
	   
	   
           ); 

           $form['step12Dfield']['colP3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td>',
		           '#default_value' =>$result_step2d['reg_investigate_2']
	   
	   
           ); 
          $form['step12Dfield']['colP4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		       '#default_value' =>$result_step2d['reg_violation_2']
	   
	   
           ); 
           $form['step12Dfield']['colP5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		         '#default_value' =>$result_step2d['reg_action_2']
	   
	   
           ); 
           $form['step12Dfield']['colP6val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
		          '#suffix'=>'</td></tr>',
		            '#default_value' =>$result_step2d['reg_remarks_2']
	   
	   
           );
           $form['step12Dfield']['colP11val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		      // '#type' => 'textfield',
              //  '#size' => 5,
             '#markup'=>'Un-regd. factories</b>',
		        '#suffix'=>'</td>',
	   
	   
           ); 


          $form['step12Dfield']['colP21val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
            
		        '#suffix'=>'</td>',
		           '#default_value' =>$result_step2d['unreg_number_2']
	   
	   
           ); 

           $form['step12Dfield']['colP31val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
           
		        '#suffix'=>'</td>',
		        '#default_value' =>$result_step2d['unreg_investigate_2']
	   
	   
           ); 
          $form['step12Dfield']['colP41val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		           '#default_value' =>$result_step2d['unreg_violation_2']
	   
	   
           ); 
           $form['step12Dfield']['colP51val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 30,
             
		        '#suffix'=>'</td>',
		             '#default_value' =>$result_step2d['unreg_action_2']
	   
	   
           ); 
           $form['step12Dfield']['colP61val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                '#cols' => 30,
		       '#suffix'=>'</td></tr></table></div>',
		     '#default_value' =>$result_step2d['unreg_remarks_2']
	   
	   
           );


$form['step12Dfield']['head33a'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<div class="table-panel-hedaer"><b> 3. Prosecution  </b></div>',

		          '#suffix'=>'</div></div>',
	   
	   
           );

       
     $form['step12Dfield']['colQ1'] = array
              (
		       '#prefix' => '<div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> 3.Name of the factory</b>',


	   
	   
           );
               

             $form['step12Dfield']['colQ2'] = array
              (
		       '#prefix' => '<th >', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Section-Rules violated  </b>',


	   
	   
           );  

            $form['step12Dfield']['colQ3'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Case No.  </b>',


	   
	   
           );      
 $form['step12Dfield']['colQ4'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th>',

		            
		       '#markup'=>'<b> Amount of fines posted  </b>',


	   
	   
           ); 

           $form['step12Dfield']['colQ5'] = array
              (
		       '#prefix' => '<th>', 
		     

		       '#suffix'=>'</th></tr></thead>',

		            
		       '#markup'=>'<b> Remarks if any  </b>',


	   
	   
           ); 

           

           $form['step12Dfield']['colQ1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textarea',
		          
                '#rows' => 2,
                 '#cols' => 2,
            
		        '#suffix'=>'</td>',
	   
	   
           ); 


          $form['step12Dfield']['colQ2val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textarea',
		          
                '#rows' => 5,
                 '#cols' => 5,
            
		        '#suffix'=>'</td>',
	   
	   
           ); 

           $form['step12Dfield']['colQ3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
           
		        '#suffix'=>'</td>',
	   
	   
           ); 
          $form['step12Dfield']['colQ4val'] = array
              (
		       '#prefix' => ' <td  >', 
		        '#type' => 'textfield',
                '#size' => 5,
             
		        '#suffix'=>'</td>',
	   
	   
           ); 
           $form['step12Dfield']['colQ5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,
             
		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           ); 
          

      
            $form['step12Dfield']['ajax_add_pw'] = array(
	
	 
	   '#prefix' => '<div class="row"><div class="col-sm-12" style="text-align:center;" >',
        '#suffix' => '</div></div>',
	   '#type' => 'button',
		'#event' => 'click',
	
		 //  '#attributes' => array('class' => array('estab-btn-pad')),
        //'#disabled' => TRUE, 
        '#default_value' => 'Add Prosecution  ',
        

          '#ajax' => array(
                                                              'callback' => 'add_step12d_data',
                                                              'wrapper' => 'data12d_show',
                                                               'method' => 'html',
                                                               'effect' => 'fade'
                                                               )
		
    );

$output4='';
 $query_tab_12_d=db_query('select  *  from labour_factory_statcell_annual_report_attach_maternity_wages where  maternity_wages_id = :anid and maternity_wages_type = :mwt', array(':anid' => trim($filenumber) , ':mwt' => 'WAGES'));
      if($query_tab_12_d->rowCount() > 0) 
              { 
       $output4 = "<div class='table-responsive'>
			   <table class='table table-striped table-bordered table-responsive add-employee-table-view'><thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the factory. </th>
	    <th >Section-Rules violated </th>
       
		 <th >Case No.</th>

		 <th >Amount of fines posted</th>
       
		 <th >Remarks</th>

		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_12_d as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $maternity_wages_id = $squan->maternity_wages_id; 
	          $maternity_wages_type=$squan->maternity_wages_type;
			
              
            
              
			 // $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab12d-del/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output4 .= "";
				 }
				else
				{
				$output4 .= "";
				}
				$output4.= "<td>".$i."</td>"; 
				$output4.= "<td>".$squan->factory_name_3."</td>";
			    $output4.= "<td>".$squan->section_rules_3."</td>";
                $output4.= "<td>".$squan->case_number_3."</td>";
                $output4.= "<td>".$squan->amount_fine_3."</td>";
                 $output4.= "<td>".$squan->remarks_3."</td>";
               
			
				$output4.= "<td >".$del_preper."</td>";
			
              
			   $output4 .= "</tr>";
	          }
              $output4 .= "</table>"; 
          }

$form['step12Dfield']['data12b'] = array(
	 	'#prefix' => '<div align="left" id="data12d_show">'.$output4,
		'#suffix' => '</div>',
       
	);

       
$form['step12Dfield']['head33b'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<div class="table-panel-header"><b> 3. Prosecution  </b></div>',

		          '#suffix'=>'</div></div>',
	   
	   
           );

           $form['step12Dfield']['colR1'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-4">', 
		     

		          '#suffix'=>'</div>',

		            '#type' => 'textfield',
		              '#size' => 5,

		                '#title' =>"	a)	No. of case pending at the beginning of the year",

                    '#default_value' =>$result_step2d['case_pending_at_beginning_3_a']
	   
	   
           );


               
    $form['step12Dfield']['colR2'] = array
              (
		       '#prefix' => '<div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"	b)	No. of case in disposed off during the year",
		        '#suffix'=>'</div>',
		         '#default_value' =>$result_step2d['case_disposed_3_b']
	   
	   
           ); 

      $form['step12Dfield']['colR3'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div></div>',
		         '#title' =>"	c)	No. of case pending at the end of the year",
		        '#default_value' =>$result_step2d['case_pending_at_end_3_c']
	   
	   
           ); 



$form['step12Dfield']['head111'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-12">', 
		       '#markup'=>'<div class="table-panel-header"><b> 4. Information regarding applications filed during the year before the authority under the P.W Act  </b></div>',

		          '#suffix'=>'</div></div>',
	   
	   
           );
  $form['step12Dfield']['colS1'] = array
              (
		       '#prefix' => '<div class="row"><div class="col-sm-4">', 
		     

		          '#suffix'=>'</div>',

		            '#type' => 'textfield',
		              '#size' => 20,

		                '#title' =>"a.	Name of the factories",

               '#default_value' =>$result_step2d['factories_name_4_a']


	   
	   
           );


               
    $form['step12Dfield']['colS2'] = array
              (
		       '#prefix' => '<div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,
             '#title' =>"	b.	Total number of applications filed",
		        '#suffix'=>'</div>',
		         '#default_value' =>$result_step2d['application_filed_4_b']
	   
	   
           ); 

      $form['step12Dfield']['colS3'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"	c.	Total number of persons involved",
		          '#default_value' =>$result_step2d['person_involved_4_c']
	   
	   
           ); 



            $form['step12Dfield']['colS4'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"	d.	Total amount of unpaid wages claimed",
		           '#default_value' =>$result_step2d['wages_claimed_4_d']
	   
	   
           );
$form['step12Dfield']['colS5'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"	e.	Total amount of un-authorised deductions claimed",
	         '#default_value' =>$result_step2d['deduction_claimed_4_e']
	   
           );

           $form['step12Dfield']['colS6'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"	f.	Number of applications pending at the beginning of the year",
	            '#default_value' =>$result_step2d['app_pending_at_beginning_4_f']
	   
           );

             $form['step12Dfield']['colS7'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div>',
		         '#title' =>"	g.	Number of applications disposed off during the year",
		           '#default_value' =>$result_step2d['app_disposed_4_g']
	   
	   
           );

  $form['step12Dfield']['colS8'] = array
              (
		       '#prefix' => ' <div class="col-sm-4">', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</div></div>',
		         '#title' =>"	h.	Number of applications pending at the end of the year",
		           '#default_value' =>$result_step2d['app_pending_at_end_4_h']
	   
	   
           );

			$form['step12Dfield']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save '),
																	'#submit' => array('step12_partpw_save'),
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }



function step12_parta_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$colA1val=trim($val['colA1']); if(!$colA1val)  $colA1val= NULL;   
	$colA2val=trim($val['colA2']); if(!$colA2val)  $colA2val= NULL;   
	$colA3val=trim($val['colA3']); if(!$colA3val)  $colA3val= NULL;   

	$colA4val=trim($val['colA4']); if(!$colA4val)  $colA4val= NULL;   
    $colA5val=trim($val['colA5']); if(!$colA5val)  $colA5val= NULL;   
    $colA6val=trim($val['colA6']); if(!$colA6val)  $colA6val= NULL;   
    $colA7val=trim($val['colA7']); if(!$colA7val)  $colA7val= NULL;   
    $colA8val=trim($val['colA8']); if(!$colA8val)  $colA8val= NULL; 
    $colA9val=trim($val['colA9']); if(!$colA9val)  $colA9val= NULL;
    $colA10val=trim($val['colA10']); if(!$colA10val)  $colA10val= NULL;



   




     $txn = db_transaction();
	  try {

                  $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_attach_construct_t1 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_attach_construct_t1');
      $query_update_B->fields(array(
		    'unit_visited' =>$colA1val, 'visit_paid' => $colA2val, 'violation' => $colA3val,  'accident' => $colA4val, 'fatal' => $colA5val, 'serious' => $colA6val, 'connection_accident' => $colA7val, 'complaints' => $colA8val, 'connection_complaints' => $colA9val, 'prosecution' => $colA10val ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);

	      }
	      else
	      {




	  	 $maxresult=db_query('select  max(construction_row_id) maxsl from labour_factory_statcell_annual_report_attach_construct_t1');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;


 $fieldsE = array('construction_row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'unit_visited' =>$colA1val, 'visit_paid' => $colA2val, 'violation' => $colA3val,  'accident' => $colA4val, 'fatal' => $colA5val, 'serious' => $colA6val, 'connection_accident' => $colA7val, 'complaints' => $colA8val, 'connection_complaints' => $colA9val, 'prosecution' => $colA10val);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_attach_construct_t1')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);
                    }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                   drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	

 }


function step12_partb_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_attach_construct_t2')
    ->condition('annual_inspection_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }

  function add_step12b_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colB11val=trim($val['colB11val']);   
      $colB12val=trim($val['colB12val']);   
      $colB13val=trim($val['colB13val']);   
      $colB14val=trim($val['colB14val']);     
     
     


   if(!$colB11val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   case no <b>    </font>";
	  exit;
	 } 

	 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_attach_construct_t2 ');
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'case_no' =>$colB11val ,'violation' =>$colB12val,'court' =>$colB13val, 'remarks' => $colB14val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_attach_construct_t2')->fields($fieldsE)->execute();	
	 
	 
	$query_tab_12_b=db_query('select  *  from labour_factory_statcell_annual_report_attach_construct_t2 where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
    
       $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Case No. </th>
	    <th >Violation </th>
       
		 <th >Court</th>

		 <th >Remarks</th>
       
		
		 
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_12_b as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $case_no=$squan->case_no;
			  $violation=$squan->violation;
			  $court=$squan->court;
              $remarks=$squan->remarks;
              
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab12b-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output1 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output1 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$case_no."</td>";
			    $output1.= "<td>".$violation."</td>";
                $output1.= "<td>".$court."</td>";
                $output1.= "<td>".$remarks."</td>";
               
			
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table>"; 
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output1 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output1;
		                  exit;
                          
                          }


      function annual_report_step12c_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$colC1=trim($val['colC1']); if(!$colC1)  $colC1= NULL;   
	$colC2=trim($val['colC2']); if(!$colC2)  $colC2= NULL;   
	$colC3=trim($val['colC3']); if(!$colC3)  $colC3= NULL; 
	$colC4=trim($val['colC4']); if(!$colC4)  $colC4= NULL;
	$colC5=trim($val['colC5']); if(!$colC5)  $colC5= NULL;  

	$colD2val=trim($val['colD2val']); if(!$colD2val)  $colD2val= NULL;   
    $colD3val=trim($val['colD3val']); if(!$colD3val)  $colD3val= NULL;   
    $colD4val=trim($val['colD4val']); if(!$colD4val)  $colD4val= NULL;   
    $colD5val=trim($val['colD5val']); if(!$colD5val)  $colD5val= NULL;   
    $colD6val=trim($val['colD6val']); if(!$colD6val)  $colD6val= NULL; 



    $colD21val=trim($val['colD21val']); if(!$colD21val)  $colD21val= NULL;   
	$colD31val=trim($val['colD31val']); if(!$colD31val)  $colD31val= NULL;   
	$colD41val=trim($val['colD41val']); if(!$colD41val)  $colD41val= NULL;   
    $colD51val=trim($val['colD51val']); if(!$colD51val)  $colD51val= NULL;   
    $colD61val=trim($val['colD61val']); if(!$colD61val)  $colD61val= NULL; 


    $colF1=trim($val['colF1']); if(!$colF1)  $colF1= NULL;   
    $colF2=trim($val['colF2']); if(!$colF2)  $colF2= NULL;   
    $colF3=trim($val['colF3']); if(!$colF3)  $colF3= NULL; 




     $txn = db_transaction();
	  try {

                  $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_attach_maternity_t1 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_attach_maternity_t1');
      $query_update_B->fields(array(
		    'no_act_and_rules_1_a' =>$colC1, 'no_non_maintenance_muster_roll_1_b' => $colC2, 'no_imp_maintenance_1_c' => $colC3, 'maternity_benefit_1_d' => $colC4, 'others_1_e' => $colC5, 'regd_number_2' => $colD2val, 'reg_investigate_2' => $colD3val, 'reg_violation_2' => $colD4val, 'reg_action_2' => $colD5val, 'reg_remarks_2' => $colD6val, 'unreg_number_2' => $colD21val, 'unreg_investigate_2' => $colD31val, 'unreg_violation_2' => $colD41val,'unreg_action_2' => $colD51val,'unreg_remarks_2' => $colD61val,'case_pending_at_beginning_4_a' => $colF1,'case_disposed_4_b' => $colF2
 ,'case_pending_at_end_4_c' => $colF3 ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);

	      }
	      else
	      {




	  	 $maxresult=db_query('select  max(maternity_row_id) maxsl from labour_factory_statcell_annual_report_attach_maternity_t1');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;

 $fieldsE = array('maternity_row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'no_act_and_rules_1_a' =>$colC1, 'no_non_maintenance_muster_roll_1_b' => $colC2, 'no_imp_maintenance_1_c' => $colC3, 'maternity_benefit_1_d' => $colC4, 'others_1_e' => $colC5, 'regd_number_2' => $colD2val, 'reg_investigate_2' => $colD3val, 'reg_violation_2' => $colD4val, 'reg_action_2' => $colD5val, 'reg_remarks_2' => $colD6val, 'unreg_number_2' => $colD21val, 'unreg_investigate_2' => $colD31val, 'unreg_violation_2' => $colD41val,'unreg_action_2' => $colD51val,'unreg_remarks_2' => $colD61val,'case_pending_at_beginning_4_a' => $colF1,'case_disposed_4_b' => $colF2
 ,'case_pending_at_end_4_c' => $colF3);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_attach_maternity_t1')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);
                    }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                   drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	

 }   

  function step12_partc_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid= encryption_decryption_fun('decrypt', trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_attach_maternity_wages')
    ->condition('maternity_wages_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }                   


  function add_step12c_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colE1val=trim($val['colE1val']);   
      $colE2val=trim($val['colE2val']);   
      $colE3val=trim($val['colE3val']);   
      $colE4val=trim($val['colE4val']); if(!$colE4val)   $colE4val= NULL;  
      $colE5val=trim($val['colE5val']);    
     
     


   if(!$colE1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   factory name <b>    </font>";
	  exit;
	 } 
    if($colE4val){
	if(!is_numeric(trim($colE4val)))
	   {
	      
	    drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   Amount of fines numeric value  <b>    </font>";
	  exit;
	}

}
     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_attach_maternity_wages ');
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'maternity_wages_id' => $inspectionid,'maternity_wages_type' =>'MATERNITY' ,'factory_name_3' =>$colE1val,'section_rules_3' =>$colE2val, 'case_number_3' => $colE3val, 'amount_fine_3' => $colE4val, 'remarks_3' => $colE5val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_attach_maternity_wages')->fields($fieldsE)->execute();	
	 
	 
	 $query_tab_12_c=db_query('select  *  from labour_factory_statcell_annual_report_attach_maternity_wages where  maternity_wages_id = :anid and maternity_wages_type = :mwt', array(':anid' => trim($inspectionid) , ':mwt' => 'MATERNITY'));
    
       $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the factory. </th>
	    <th >Section-Rules violated </th>
       
		 <th >Case No.</th>

		 <th >Amount of fines posted</th>
       
		 <th >Remarks</th>

		 
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_12_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $maternity_wages_id = $squan->maternity_wages_id; 
	          $maternity_wages_type=$squan->maternity_wages_type;
			
              
            
              
			 // $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab12c-del/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output2 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output2 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output2.= "<td>".$i."</td>"; 
				$output2.= "<td>".$squan->factory_name_3."</td>";
			    $output2.= "<td>".$squan->section_rules_3."</td>";
                $output2.= "<td>".$squan->case_number_3."</td>";
                $output2.= "<td>".$squan->amount_fine_3."</td>";
                 $output2.= "<td>".$squan->remarks_3."</td>";
               
			
				$output2.= "<td >".$del_preper."</td>";
			
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table>"; 
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output2 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output2;
		                  exit;
                          
                          }


      function step12_partpw_save($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    //part A
	$colO1=trim($val['colO1']); if(!$colO1)  $colO1= NULL;   
	$colO2=trim($val['colO2']); if(!$colO2)  $colO2= NULL;   
	$colO3=trim($val['colO3']); if(!$colO3)  $colO3= NULL;   

	$colO4=trim($val['colO4']); if(!$colO4)  $colO4= NULL;   
    $colO5=trim($val['colO5']); if(!$colO5)  $colO5= NULL;   
    $colO6=trim($val['colO6']); if(!$colO6)  $colO6= NULL;   
    $colO7=trim($val['colO7']); if(!$colO7)  $colO7= NULL;   
    $colO8=trim($val['colO8']); if(!$colO8)  $colO8= NULL;


    $colP2val=trim($val['colP2val']); if(!$colP2val)  $colP2val= NULL;
    $colP3val=trim($val['colP3val']); if(!$colP3val)  $colP3val= NULL;
    $colP4val=trim($val['colP4val']); if(!$colP4val)  $colP4val= NULL;
     $colP5val=trim($val['colP5val']); if(!$colP5val)  $colP5val= NULL;
      $colP6val=trim($val['colP6val']); if(!$colP6val)  $colP6val= NULL;

     $colP21val=trim($val['colP21val']); if(!$colP21val)  $colP21val= NULL;
      $colP31val=trim($val['colP31val']); if(!$colP31val)  $colP31val= NULL;
      $colP41val=trim($val['colP41val']); if(!$colP41val)  $colP41val= NULL;
      $colP51val=trim($val['colP51val']); if(!$colP51val)  $colP51val= NULL;
       $colP61val=trim($val['colP61val']); if(!$colP61val)  $colP61val= NULL;


     $colR1=trim($val['colR1']); if(!$colR1)  $colR1= NULL;
      $colR2=trim($val['colR2']); if(!$colR2)  $colR2= NULL;
       $colR3=trim($val['colR3']); if(!$colR3)  $colR3= NULL;
   

      $colS1=trim($val['colS1']); if(!$colS1)  $colS1= NULL;
      $colS2=trim($val['colS2']); if(!$colS2)  $colS2= NULL;
      $colS3=trim($val['colS3']); if(!$colS3)  $colS3= NULL;
      $colS4=trim($val['colS4']); if(!$colS4)  $colS4= NULL;
      $colS5=trim($val['colS5']); if(!$colS5)  $colS5= NULL;
      $colS6=trim($val['colS6']); if(!$colS6)  $colS6= NULL;
      $colS7=trim($val['colS7']); if(!$colS7)  $colS7= NULL;
      $colS8=trim($val['colS8']); if(!$colS8)  $colS8= NULL;
      


     $txn = db_transaction();
	  try {

                  $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_attach_wages_t1 where  annual_inspection_id = :filenumber', array(':filenumber' => $inspectionid));


             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_attach_wages_t1');
      $query_update_B->fields(array(
		    'no_act_and_rules_1_a' =>$colO1, 'no_notice_dates_payment_1_b' => $colO2, 'no_non_maintenance_wages_1_c' => $colO3,  'no_imp_maintenance_wages_1_d' => $colO4, 'no_recording_date_payment_1_e' => $colO5, 'no_register_wages_1_f' => $colO6, 'no_delayed_wages_1_g' => $colO7, 'no_others_1_h' => $colO8, 'regd_number_2' => $colP2val, 'reg_investigate_2' => $colP3val, 'reg_violation_2' => $colP4val, 'reg_action_2' => $colP5val, 'reg_remarks_2' => $colP6val, 'unreg_number_2' => $colP21val, 'unreg_investigate_2' => $colP31val, 'unreg_violation_2' => $colP41val, 'unreg_action_2' => $colP51val, 'unreg_remarks_2' => $colP61val, 'case_pending_at_beginning_3_a' => $colR1, 'case_disposed_3_b' => $colR2, 'case_pending_at_end_3_c' => $colR3, 'factories_name_4_a' => $colS1, 'application_filed_4_b' => $colS2, 'person_involved_4_c' => $colS3, 'wages_claimed_4_d' => $colS4, 'deduction_claimed_4_e' => $colS5, 'app_pending_at_beginning_4_f' => $colS6, 'app_disposed_4_g' => $colS7, 'app_pending_at_end_4_h' => $colS8 ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 
        $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);

	      }
	      else
	      {




	  	 $maxresult=db_query('select  max(wages_row_id) maxsl from labour_factory_statcell_annual_report_attach_wages_t1');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;


 $fieldsE = array('wages_row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'no_act_and_rules_1_a' =>$colO1, 'no_notice_dates_payment_1_b' => $colO2, 'no_non_maintenance_wages_1_c' => $colO3,  'no_imp_maintenance_wages_1_d' => $colO4, 'no_recording_date_payment_1_e' => $colO5, 'no_register_wages_1_f' => $colO6, 'no_delayed_wages_1_g' => $colO7, 'no_others_1_h' => $colO8, 'regd_number_2' => $colP2val, 'reg_investigate_2' => $colP3val, 'reg_violation_2' => $colP4val, 'reg_action_2' => $colP5val, 'reg_remarks_2' => $colP6val, 'unreg_number_2' => $colP21val, 'unreg_investigate_2' => $colP31val, 'unreg_violation_2' => $colP41val, 'unreg_action_2' => $colP51val, 'unreg_remarks_2' => $colP61val, 'case_pending_at_beginning_3_a' => $colR1, 'case_disposed_3_b' => $colR2, 'case_pending_at_end_3_c' => $colR3, 'factories_name_4_a' => $colS1, 'application_filed_4_b' => $colS2, 'person_involved_4_c' => $colS3, 'wages_claimed_4_d' => $colS4, 'deduction_claimed_4_e' => $colS5, 'app_pending_at_beginning_4_f' => $colS6, 'app_disposed_4_g' => $colS7, 'app_pending_at_end_4_h' => $colS8);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_attach_wages_t1')->fields($fieldsE)->execute();

                       $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);
                    }
                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                   drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	

 }                    


 function add_step12d_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colQ1val=trim($val['colQ1val']);   
      $colQ2val=trim($val['colQ2val']);   
      $colQ3val=trim($val['colQ3val']);   
      $colQ4val=trim($val['colQ4val']); if(!$colQ4val)   $colQ4val= NULL; 
      $colQ5val=trim($val['colQ5val']);      
     
     


   if(!$colQ1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   factory name <b>    </font>";
	  exit;
	 } 

	if($colQ4val){
	if(!is_numeric(trim($colQ4val)))
	   {
	      
	    drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   Amount of fines numeric value  <b>    </font>";
	  exit;
	}

} 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_attach_maternity_wages ');
	foreach($ins_pr_person as $energy) {
	
	    $ownermax = $energy->ownermax; 
        
		
	}
		
	 if($ins_pr_person->rowCount()==0) 
        { 
		$count_profile=1;
		}
		else
		{
		$count_profile=$ownermax+1;	
			
		}
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'maternity_wages_id' => $inspectionid,'maternity_wages_type' =>'WAGES' ,'factory_name_3' =>$colQ1val,'section_rules_3' =>$colQ2val, 'case_number_3' => $colQ3val, 'amount_fine_3' => $colQ4val, 'remarks_3' => $colQ5val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_attach_maternity_wages')->fields($fieldsE)->execute();	
	 
	 
	 $query_tab_12_d=db_query('select  *  from labour_factory_statcell_annual_report_attach_maternity_wages where  maternity_wages_id = :anid and maternity_wages_type = :mwt', array(':anid' => trim($inspectionid) , ':mwt' => 'WAGES'));
    
       $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the factory. </th>
	    <th >Section-Rules violated </th>
       
		 <th >Case No.</th>

		 <th >Amount of fines posted</th>
       
		 <th >Remarks</th>

		 
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_12_d as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $maternity_wages_id = $squan->maternity_wages_id; 
	          $maternity_wages_type=$squan->maternity_wages_type;
			
              
            
              
			 // $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab12d-del/'.encryption_decryption_fun('encrypt',$maternity_wages_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		      $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  
			  
			  
              if($i%2==0){
		        $output2 .= "<tr bgcolor=\"#FCF6CF\">";
				 }
				else
				{
				$output2 .= "<tr bgcolor=\"#FEFEF2\">";
				}
				$output2.= "<td>".$i."</td>"; 
				$output2.= "<td>".$squan->factory_name_3."</td>";
			    $output2.= "<td>".$squan->section_rules_3."</td>";
                $output2.= "<td>".$squan->case_number_3."</td>";
                $output2.= "<td>".$squan->amount_fine_3."</td>";
                 $output2.= "<td>".$squan->remarks_3."</td>";
               
			
				$output2.= "<td >".$del_preper."</td>";
			
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table>"; 
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output2 = ' DATA NOT INSERT';
  }  
	


                          drupal_get_messages(error);
		                  return $output2;
		                  exit;
                          
                          }


   function step12_partd_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid= encryption_decryption_fun('decrypt', trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_attach_maternity_wages')
    ->condition('maternity_wages_id',trim($filenumber))
	->condition('row_id',trim($rowid))
    ->execute();
	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step12/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }                        