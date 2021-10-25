<?php

function annual_report_list( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	   $uid	=	$user->uid; 

$form['#attached']['js'] = array(drupal_get_path('module', 'annual_report') . '/js/annualreport.js',);	
   
$thisYear = date("Y")-1;
              $form['annulreportfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  Annual Report :'.$thisYear.'  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
   $form['annulreportfield']['uid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $uid,
	   
	   );

        

        $form['report_for_option'] = array(
	     '#type' => 'value',
      
		   '#value' => array('CALENDAR'=>t('Calendar Year'),'FINANCIAL'=>t('Financial Year'))
		
         );
	
	
	
		$form['annulreportfield']['annual_report'] = array(
		
        '#type' => 'select',
        '#title'=>'Report For:',
		'#required' => TRUE,
        '#options' => $form['report_for_option']['#value'],
	      '#prefix' => '<div class="row"><div class="col-sm-12">', 
   
		    '#suffix'=>'</div>',

		    '#attributes' => array('onchange' => 'annualReport(this.value);','class' => array('select-estab-shop')),
		
		
		
				
        
            );


            $form['annulreportfield']['from'] = array
              (
		       '#prefix' => '<div class="col-sm-6">', 
		       	'#title'=>'From:',
		       '#type' => 'textfield',
                '#size' => 12,

		        '#suffix'=>'</div>',
		        '#attributes' => array('readonly' => 'readonly'),
	           '#required' => TRUE,
	   
           ); 

           $form['annulreportfield']['to'] = array
              (
		       '#prefix' => ' <div class="col-sm-6">', 
		       '#type' => 'textfield',
                '#size' => 12,
              	'#title'=>'To:',
		        '#suffix'=>'</div>',
		        '#attributes' => array('readonly' => 'readonly'),
		         '#required' => TRUE,
	   
	   
           ); 

         

	   
	   
	   
	   
          	$form['annulreportfield']['submit_button']	= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" class="col-sm-4" >',
                                                                 '#suffix'=>'</div></div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Next ')
																);
		 
	
	  
		 
	 $rows = array();
    $header = array();

    	$header = array(
          array('data'=> 'SL.NO', 'class' => array('')),
		  array('data' => ' YEAR',   'class' => array('')),
		  array('data'=> 'From - To', 'class' => array('')),
          array('data' => 'Area', 'class' => array('')),
		  array('data' => 'EDIT', 'class' => array('')),
		 
		 
		 
		 
	);	

	$sort = 'DESC';
	$order = 'annual_inspection_id';
	$annual_list_query = db_select('labour_factory_statcell_annual_report', 't');
	
	
	
	$annual_list_query->fields('t',array('annual_inspection_id','inspector_id','report_from_date','report_to_date',
	'report_year','annual_form_type','status','submit_date','area','e_note','create_date','create_by'));
	$annual_list_query->condition('t.inspector_id',trim($uid),'=');
	
	$annual_list_query = $annual_list_query->extend('TableSort')->extend('PagerDefault')->limit(15);
	$annual_list_query->orderBy($order, $sort);
	$annual_list_query_result = $annual_list_query->execute();
	
	//print $ins_list_query;
	$i=0;
	foreach($annual_list_query_result as $data){
		$i++;

		   $kk=$base_root.$base_path.'admin/annual-report/'.$data->annual_inspection_id;
		   $link_create_annual_report=l(t('<font color="DarkGreen"><b>EDIT</b></font></br>'), $kk,array('html'=>TRUE)) ;

	$rows[] = array(
      				
					$i,
					
					$data->report_year,
					
					date('d/m/Y', strtotime($data->report_from_date)).'-'.date('d/m/Y', strtotime($data->report_to_date)),
					
					NULL,
					$link_create_annual_report,
					
					
					
				);


}
				$variables = array(
	  			'attributes' 		=> array('class' => array('clra_applications')), 
	  			'header' 			=> $header,
	  			'rows'				=> $rows,
		);
		$output = theme('table', $variables).theme("pager");
	     $form['inspectionlistfields']['addshowprin'] = array(
					'#markup'=>$output,
					);
	
		

	   
	
	   
       return $form; 
  }


function annual_report_list_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);
//exit;


    $annual_report=trim($val['annual_report']);
	$uid=trim($val['uid']);
	$from=trim($val['from']);
	$to=trim($val['to']);
	$thisYear = date("Y")-1;

 $txn = db_transaction();
	  try {
            $maxresult=db_query('select  max(annual_inspection_id) maxsl from labour_factory_statcell_annual_report');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;
	     
		     $area=NULL;

	       
	        
	 
		  



                         $fieldsE = array('annual_inspection_id' => $autoGENNO, 'inspector_id' =>$uid,'area' =>NULL, 'report_from_date' => $from, 'report_to_date' => $to, 'report_year' => $thisYear, 'annual_form_type' => $annual_report, 'status' => 'I', 'remarks' => NULL
                         , 'status_code' => NULL, 'last_updated' => date("Y-m-d"), 'is_submitted' => 0, 'submit_date' => date("Y-m-d"), 'is_processing' => 0 , 'is_accepted' => 0, 'accept_by' => 0, 'accept_date' => NULL, 'e_note' => NULL,'processed_data' => NULL ,'is_disabled' => 0,'create_by' => 0,'create_date' => date("Y-m-d"));
		  
		   
           db_insert('labour_factory_statcell_annual_report')->fields($fieldsE)->execute();	
	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				  $full_base=$base_root.$base_path.'admin/annual-report/'.$autoGENNO;
	           
	             drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report-list';

             $message = 'ANNUAL REPORT NOT PROCEED   . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	
	
}





function annual_report_step1( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
	 //print $id;
	 $form['step1field'] = array(
          '#title' => t('<font color="DarkGreen"><b> Inspection (A).  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		$form['step1field']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );

														
		
       
	
	  
		 
	 
	
	      
	
	
	
		
	

		
     $form['step1field']['one'] = array
              (
		       '#prefix' => '<table border="1"><tr><td rowspan="4" >', 
		       '#markup'=>'<b> Group  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	


            $form['step1field']['two'] = array
              (
		       '#prefix' => '<td colspan="8" style="text-align:center;">', 
		       '#markup'=>'<b> No. of units visited  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	


             $form['step1field']['three'] = array
              (
		       '#prefix' => '<tr><td colspan="3" >', 
		       '#markup'=>'<b> Registered factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1field']['four'] = array
              (
		       '#prefix' => '<td colspan="3" >', 
		       '#markup'=>'<b> Unregistered amenable factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1field']['five'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Not amenable factories  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1field']['six'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Total </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1field']['2mone'] = array
              (
		       '#prefix' => '<tr><td colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b>2(m)  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
            	

            $form['step1field']['85one'] = array
              (
		       '#prefix' => '<td rowspan="2"  >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['2mtwo'] = array
              (
		       '#prefix' => '<td  colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b> 2(m) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1field']['85two'] = array
              (
		       '#prefix' => '<td rowspan="2" >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1field']['romani'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1field']['romanii'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['romaniii'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
           $form['step1field']['romaniv'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii)</b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1field']['Gf'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>G </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1field']['Gfone'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1field']['Gftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1field']['Gfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1field']['Gffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1field']['Gffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Gfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Gfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['Gfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
           );	

            $form['step1field']['Hf'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>H </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1field']['Hfone'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1field']['Hftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1field']['Hfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1field']['Hffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1field']['Hffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Hfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['Hfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['Hfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
           );	

            $form['step1field']['MAHf'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>MAH </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1field']['MAHfone'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1field']['MAHftwo'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1field']['MAHfthree'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1field']['MAHffour'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1field']['MAHffive'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['MAHfsix'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1field']['MAHfseven'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1field']['MAHfeight'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr></table>',
	   
	   
           );	


   // Part B 


   $form['step1Bfield'] = array(
          '#title' => t('<font color="DarkGreen"><b> Inspection (B)   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		

														
		
       
	
	  
		 
	 
	
	      
	
	
	
		
	

		
     $form['step1Bfield']['oneB'] = array
              (
		       '#prefix' => '<table border="1"><tr><td rowspan="4" >', 
		       '#markup'=>'<b> Group  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	


            $form['step1Bfield']['twoB'] = array
              (
		       '#prefix' => '<td colspan="8" style="text-align:center;">', 
		       '#markup'=>'<b> No. of visits paid to </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	


             $form['step1Bfield']['threeB'] = array
              (
		       '#prefix' => '<tr><td colspan="3" >', 
		       '#markup'=>'<b> Registered factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1Bfield']['fourB'] = array
              (
		       '#prefix' => '<td colspan="3" >', 
		       '#markup'=>'<b> Unregistered amenable factories u/s  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1Bfield']['fiveB'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Not amenable factories  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
             $form['step1Bfield']['sixB'] = array
              (
		       '#prefix' => '<td rowspan="3" >', 
		       '#markup'=>'<b> Total </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1Bfield']['2moneB'] = array
              (
		       '#prefix' => '<tr><td colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b>2(m)  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
            	

            $form['step1Bfield']['85oneB'] = array
              (
		       '#prefix' => '<td rowspan="2"  >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['2mtwoB'] = array
              (
		       '#prefix' => '<td  colspan="2" style="text-align:center;">', 
		       '#markup'=>'<b> 2(m) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1Bfield']['85twoB'] = array
              (
		       '#prefix' => '<td rowspan="2" >', 
		       '#markup'=>'<b>85 </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1Bfield']['romaniB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

            $form['step1Bfield']['romaniiB'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['romaniiiB'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(i) </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
           $form['step1Bfield']['romanivB'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b>(ii)</b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );	

           $form['step1Bfield']['GfB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>G </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1Bfield']['GfoneB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Bfield']['GftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Bfield']['GfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Bfield']['GffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1Bfield']['GffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['GfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['GfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['GfeightddB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
           );	

            $form['step1Bfield']['HfB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>H </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1Bfield']['HfoneB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Bfield']['HftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Bfield']['HfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Bfield']['HffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1Bfield']['HffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['HfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['HfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['HfeightB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr>',
	   
	   
           );	

            $form['step1Bfield']['MAHfB'] = array
              (
		       '#prefix' => '<tr><td >', 
		       '#markup'=>'<b>MAH </b>',

		          '#suffix'=>'</td>',
	   
	   
           );	

               $form['step1Bfield']['MAHfoneB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		       '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Bfield']['MAHftwoB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Bfield']['MAHfthreeB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Bfield']['MAHffourB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
		         '#size' => 2,

		          '#suffix'=>'</td>',
	   
	   
           );
			 $form['step1Bfield']['MAHffiveB'] = array
              (
		       '#prefix' => '<td >', 
		       '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['MAHfsixB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	

           $form['step1Bfield']['MAHfsevenB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                 '#size' => 2,
		          '#suffix'=>'</td>',
	   
	   
           );	
            $form['step1Bfield']['MAHfeightB'] = array
              (
		       '#prefix' => '<td >', 
		      '#type' => 'textfield',
                  '#size' => 2,
		          '#suffix'=>'</td></tr></table>',
	   
	   
           );           




     // Part 3

              $form['step1Cfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  C.Frequency of Visit.  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
	
	        
		
$form['step1Cfield']['col1'] = array
              (
		       '#prefix' => '<table border="1"><tr><td rowspan="2" >', 
		       '#markup'=>'<b> Frequency  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Cfield']['col2'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> Factories other than defence installations  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


               $form['step1Cfield']['col3'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> Defence Installation  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Cfield']['col4'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b>TOTAL  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );

               $form['step1Cfield']['col5'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#markup'=>'<b>Regd.  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Cfield']['col6'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>Un-registered (Amenable & Non-Amenable).  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Cfield']['col7'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>Regd..  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                  $form['step1Cfield']['col8'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>	Un-registered (Amenable & Non-Amenable)..  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step1Cfield']['col9'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>Regd..  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Cfield']['col10'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#markup'=>'<b>	Un-registered (Amenable & Non-Amenable)..  </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );
        

        $form['frquency_option'] = array(
	     '#type' => 'value',
         //'#value' => array('0'=>t('select'),'1'=>t('Male(M)'),'2'=>t('Female(F)'),'3'=>t('Transgender'))
		   '#value' => array('0'=>t('select  '),'1'=>t('1'),'2'=>t('2'))
		
         );
	
	
	
		$form['step1Cfield']['frquency'] = array(
		
        '#type' => 'select',
       // '#title'=>'Country',
		//'#required' => TRUE,
        '#options' => $form['frquency_option']['#value'],
	      '#prefix' => ' <tr> <td  >', 
   
		    '#suffix'=>'</td>',
		
		
		
				
        
            );

              $form['step1Cfield']['col2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step1Cfield']['col3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step1Cfield']['col4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 



                $form['step1Cfield']['col5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 



                $form['step1Cfield']['col6val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

                $form['step1Cfield']['col7val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 


														
		
       $form['step1Cfield']['submit'] = array (
                          
		'#type' => 'button',
		'#event' => 'click',
		'#prefix' => '<tr><td colspan="8" style="text-align:center;">',  
         '#suffix' => '</td></tr></table>',
		   '#attributes' => array('class' => array('estab-btn-pad')),
        //'#disabled' => TRUE, 
        '#default_value' => 'ADD  ',
        '#ajax' => array(
        'callback' => 'add_emp_man_det',
        'wrapper' => 'profile_add',
        'method' => 'html',
        'effect' => 'fade'
    )
        );
	
	  
		 
	 
	
	      
	
	
	// Part 4
		
	      $form['step1Dfield'] = array(
          '#title' => t('<font color="DarkGreen"><b>  D.No. of Visits paid.  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step1Dfield']['colD1'] = array
              (
		       '#prefix' => '<table border="1"><tr><td colspan="5" >', 
		       '#markup'=>'<b> Exclusive Under  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step1Dfield']['colD2'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> During Rest Interval  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step1Dfield']['colD3'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> Before or after legal hours  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step1Dfield']['colD4'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> On Sundays/Holidays </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step1Dfield']['colD5'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> For approval of plans </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step1Dfield']['colD6'] = array
              (
		       '#prefix' => ' <td rowspan="2"  >', 
		        '#markup'=>'<b> For Renewal of licence </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

              $form['step1Dfield']['colD7'] = array
              (
		       '#prefix' => ' <tr> <td  >', 
		        '#markup'=>'<b> MSIHCR </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


                $form['step1Dfield']['colD8'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> P.W.A </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 
              $form['step1Dfield']['colD9'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> M.B.A </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

              $form['step1Dfield']['colD10'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> C.A.R. </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 

               $form['step1Dfield']['colD11'] = array
              (
		       '#prefix' => '  <td  >', 
		        '#markup'=>'<b> C.I.(P&R)A </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

               $form['step1Dfield']['misval'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 

      $form['step1Dfield']['pwdval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           ); 


              $form['step1Dfield']['mbaval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['carval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Dfield']['cival'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Dfield']['drival'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Dfield']['balhval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step1Dfield']['oshhval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );
              $form['step1Dfield']['faopval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['frolval'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr>',
	   
	   
           );

              $form['step1Dfield']['colD12'] = array
              (
		       '#prefix' => '<tr><td colspan="2">', 
		       '#markup'=>'<b> For collections of statistics </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD13'] = array
              (
		       '#prefix' => '<td colspan="2">', 
		       '#markup'=>'<b> For enquiry into complaints </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
              $form['step1Dfield']['colD14'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> To court for prosecution cases </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD15'] = array
              (
		       '#prefix' => '<td colspan="2" >', 
		       '#markup'=>'<b> To closed factories </b>',

		          '#suffix'=>'</td>',
	   
	   
           );

                $form['step1Dfield']['colD16'] = array
              (
		       '#prefix' => '<td >', 
		       '#markup'=>'<b> Others </b>',

		          '#suffix'=>'</td>',
	   
	   
           );
               $form['step1Dfield']['colD17'] = array
              (
		       '#prefix' => '<td  >', 
		       '#markup'=>'<b> Total </b>',

		          '#suffix'=>'</td></tr>',
	   
	   
           );
 $form['step1Dfield']['colD12val'] = array
              (
		       '#prefix' => '<tr> <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );


 $form['step1Dfield']['colD13val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD14val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD15val'] = array
              (
		       '#prefix' => ' <td colspan="2" >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

              $form['step1Dfield']['colD16val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td>',
	   
	   
           );

         $form['step1Dfield']['colD17val'] = array
              (
		       '#prefix' => ' <td  >', 
		    
		       '#type' => 'textfield',
                '#size' => 5,
		          '#suffix'=>'</td></tr> </table>',
	   
	   
           );


			$form['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>t(' Save ')
																);
		 
		 
	
	 	
		
		
 
		
				
	
														
														  
	        return $form; 
  }




  function annual_report_step1_submit($form , $form_state) {	


         global $base_root, $base_path,$full_base;




$val=$form_state['values'];
//print_r($val);  
//exit;
 
  $annual_inspection_id=trim($val['inspectionid']);  

  $Gfone=trim($val['Gfone']);  if(!$Gfone) $Gfone= NULL;         
  $Gftwo=trim($val['Gftwo']); if(!$Gftwo) $Gftwo= NULL;
  $Gfthree=trim($val['Gfthree']); if(!$Gfthree) $Gfthree= NULL;
  $Gffour=trim($val['Gffour']); if(!$Gffour) $Gffour= NULL;
  $Gffive=trim($val['Gffive']); if(!$Gffive) $Gffive= NULL;
  $Gfsix=trim($val['Gfsix']);   if(!$Gfsix) $Gfsix= NULL;
  $Gfseven=trim($val['Gfseven']); if(!$Gfseven) $Gfseven= NULL;
  $Gfeight=trim($val['Gfeight']); if(!$Gfeight) $Gfeight= NULL;



  $GfoneB=trim($val['GfoneB']);  if(!$GfoneB) $GfoneB= NULL;         
  $GftwoB=trim($val['GftwoB']); if(!$GftwoB) $GftwoB= NULL;
  $GfthreeB=trim($val['GfthreeB']); if(!$GfthreeB) $GfthreeB= NULL;
  $GffourB=trim($val['GffourB']); if(!$GffourB) $GffourB= NULL;
  $GffiveB=trim($val['GffiveB']); if(!$GffiveB) $GffiveB= NULL;
  $GfsixB=trim($val['GfsixB']);   if(!$GfsixB) $GfsixB= NULL;
  $GfsevenB=trim($val['GfsevenB']); if(!$GfsevenB) $GfsevenB= NULL;
  $GfeightddB=trim($val['GfeightddB']); if(!$GfeightddB) $GfeightddB= NULL;






  
    
    $txn = db_transaction();
	  try {
  
   $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t1_a_b');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $rowid=$querystring;

 $fieldsE = array('row_id' => $rowid ,'annual_inspection_id' => $annual_inspection_id, 'g_nouv_regfac_2m_i' =>$Gfone,'g_nouv_regfac_2m_ii' =>$Gftwo, 'g_nouv_regfac_85' => $Gfthree, 'g_nouv_unregfac_2m_i' => $Gffour, 'g_nouv_unregfac_2m_ii' => $Gffive, 'g_nouv_unregfac_85' => $Gfsix, 'g_nouv_non_amendable' => $Gfseven, 'g_nouv_total' => $Gfeight,

 	'g_novp_regfac_2m_i' => $GfoneB, 'g_novp_regfac_2m_ii' => $GftwoB , 'g_novp_regfac_85' => $GfthreeB
 	, 'g_novp_unregfac_2m_i' => $GffourB , 'g_novp_unregfac_2m_ii' => $GffiveB , 'g_novp_unregfac_85' => $GfsixB ,

 	'g_novp_non_amendable' => $GfsevenB , 'g_novp_total' => $GfeightddB,


 	'h_nouv_regfac_2m_i' => $GfoneB, 'h_nouv_regfac_2m_ii' => $GftwoB , 'h_nouv_regfac_85' => $GfthreeB
 	, 'h_nouv_unregfac_2m_i' => $GffourB , 'h_nouv_unregfac_2m_ii' => $GffiveB , 'h_nouv_unregfac_85' => $GfsixB ,

 	'h_nouv_non_amendable' => $GfsevenB , 'h_nouv_total' => $GfeightddB,




                         );
		  
		   
           db_insert('labour_factory_statcell_annual_report_t1_a_b')->fields($fieldsE)->execute();	
	 
	
	                  
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
                 $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      
				  $full_base=$base_root.$base_path.'admin/annual-report/'.$annual_inspection_id;
	           
	              drupal_set_message(t($message));
	              drupal_goto($full_base);

	             }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/'.$annual_inspection_id;

             $message = 'DATA NOT SAVED   . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }
	
		 
		 
	
	 	}
		
		
 
		
				
	
														
														  
	       