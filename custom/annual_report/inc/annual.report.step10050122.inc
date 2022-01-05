<?php

function annual_report_step10( $form, &$form_state, $filenumber= NULL , $row_id= NULL  ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 
		 $filenumber=encryption_decryption_fun('decrypt',$filenumber);
		 $row_id=encryption_decryption_fun('decrypt',$row_id);
	 
	
	      
	
	
	 $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id', 'report_from_date','report_to_date','report_year','annual_form_type'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
     //  $inspector_name=get_name($inspector_id);
		
	  $report_from_date=date('d-m-Y', strtotime($result_mrist['report_from_date']));
      $report_to_date=date('d-m-Y', strtotime($result_mrist['report_to_date']));

      $thisYear=$result_mrist['report_year'];
      $annual_report=$result_mrist['annual_form_type'];

     $previous_year=$thisYear - 1;
        
        //print "ssss".$previous_year;
       // exit;
   
      if($annual_report=='CALENDAR'){
		$previous_from_year_dt='1900-01-01';
	    $previous_to_year_dt=$previous_year.'-12-31';
	}
	elseif($annual_report=='FINANCIAL'){
		$previous_from_year_dt='1900-01-01';
	    $previous_to_year_dt=date("Y")."-03-31";
	}
	

		
    //print $previous_to_year_dt.'----'.$previous_from_year_dt;
	
	      
	
	
	// Part 4
		
	      $form['step10field'] = array(
          '#title' => t('<b> Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'</b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
           $form['step10field']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );
	    $form['step10field']['rowid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $row_id,
	   
	   );


	                      $factory_name=NULL;
                         $factory_address=NULL;;
                         $reg_unreg=NULL;;
                         $person_prosecuted=NULL;;
                         $case_number=NULL;;
                         $court_name=NULL;;
                         $violation_description=NULL;
                         $results=NULL;
                         $total_fine=0;
                    
                        
                       if( $filenumber &&   $row_id) 
                         { 

                         $t9_row_query = db_select('labour_factory_statcell_annual_report_t9_10', 'a');
                         $t9_row_query->condition('a.annual_inspection_id',trim($filenumber),'=');
                         $t9_row_query->condition('a.row_id',trim($row_id),'=');
                         
                       

                          $t9_row_query->fields('a',array('factory_name','factory_address',
        'reg_unreg','person_prosecuted','case_number','court_name','violation_description','results','total_fine','is_pending','is_disabled'));

                   $t9_row_query_result = $t9_row_query->execute();

                     
                       if( $t9_row_query_result->rowCount() > 0 ) 
                       { 

                      
                         $anr_t9_fetch=$t9_row_query_result->fetchAssoc();

                         $factory_name=$anr_t9_fetch['factory_name'];
                         $factory_address=$anr_t9_fetch['factory_address'];
                         $reg_unreg=$anr_t9_fetch['reg_unreg'];
                         $person_prosecuted=$anr_t9_fetch['person_prosecuted'];
                         $case_number=$anr_t9_fetch['case_number'];
                         $court_name=$anr_t9_fetch['court_name'];
                         $violation_description=$anr_t9_fetch['violation_description'];
                         $results=$anr_t9_fetch['results'];
                         $total_fine=$anr_t9_fetch['total_fine'];
                     

                       }
                   }


		
     	
$form['step10field']['col1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>10. Information relating to pending cases (Under the factories Act) of previous Year/Years.</b></div><div class="table-responsive">
			   <table class="table table-striped table-bordered table-responsive"><thead><tr><th >', 
		       '#markup'=>'<b> Name of the factory  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step10field']['col2'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Address of the factory </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step10field']['col3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Registered/un-registered factory  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step10field']['col4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Persons against whom launched <br>(Occupier, Manager etc.) </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

               $form['step10field']['col5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Case Number </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step10field']['col6'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Name of Court </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

              $form['step10field']['col7'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Sections/Rules violated <br>with a short description </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


                $form['step10field']['col8'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Result </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 
              $form['step10field']['col9'] = array
              (
		       '#prefix' => '  <th>', 
		        '#markup'=>'<b> Amount of fines</b>',
           

		        '#suffix'=>'</th></tr></thead> ',
	   
	   
           ); 

             

              $form['step10field']['col1val'] = array
              (
		       '#prefix' => '<tr> <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</td>',
		        '#required' => TRUE,
		       '#default_value' =>  $factory_name ,
	   
	   
           );
            

          $form['step10field']['col2val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</td>',
		         '#required' => TRUE,
		          '#default_value' =>  $factory_address ,
	   
	   
           );
  $form['register_option'] = array(
	     '#type' => 'value',
         //'#value' => array('0'=>t('select'),'1'=>t('Male(M)'),'2'=>t('Female(F)'),'3'=>t('Transgender'))
		   '#value' => array(''=>t('select  '),'Registered'=>t('Registered'),'UnRegistered'=>t('UnRegistered'))
		
         );
 $form['step10field']['col3val'] = array
              (
		       '#prefix' => ' <td  >', 
		          '#type' => 'select',
		       
               '#options' => $form['register_option']['#value'],
		          '#suffix'=>'</td>',
		             	'#required' => TRUE,
		             	 '#default_value' =>  $reg_unreg ,
	   
	   
           );

               $form['occupier_option'] = array(
	     '#type' => 'value',
         //'#value' => array('0'=>t('select'),'1'=>t('Male(M)'),'2'=>t('Female(F)'),'3'=>t('Transgender'))
		   '#value' => array(''=>t('select  '),'Occupier'=>t('Occupier'),'Manager'=>t('Manager'),'Occupier-Manager'=>t('Occupier-Manager'))
		
         );
 $form['step10field']['col4val'] = array
              (
		       '#prefix' => ' <td  >', 
		          '#type' => 'select',
		       
               '#options' => $form['occupier_option']['#value'],
		          '#suffix'=>'</td>',
		       
		         	'#default_value' =>  $person_prosecuted ,
	   
	   
           );

             
$form['step10field']['col5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
		           	'#required' => TRUE,

		           	  '#default_value' =>  $case_number ,
	   
	   
           ); 

                 $form['step10field']['col6val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                 '#cols' => 5,
		          '#suffix'=>'</td>',
		         '#required' => TRUE,
		          '#default_value' =>  $court_name ,
	   
	   
           );
                 $form['step10field']['col7val'] = array
              (
		       '#prefix' => ' <td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 5,
                '#cols' => 5,
		       '#suffix'=>'</td>',
		       '#required' => TRUE,
		          '#default_value' =>  $violation_description ,
	   
	   
	   
           );

               $form['case_status_option'] = array(
	     '#type' => 'value',
         //'#value' => array('0'=>t('select'),'1'=>t('Male(M)'),'2'=>t('Female(F)'),'3'=>t('Transgender'))
		   '#value' => array(''=>t('select  '),'PENDING'=>t('Pending'),'AQUITED'=>t('Aquited'),'CONVICTED'=>t('Convicted'),'WITHDRAWN'=>t('Withdrawn'),'DISPOSED'=>t('Disposed'))
		
         );
 $form['step10field']['col8val'] = array
              (
		       '#prefix' => ' <td  >', 
		          '#type' => 'select',
		       
               '#options' => $form['case_status_option']['#value'],
		          '#suffix'=>'</td>',
		          '#required' => TRUE,
		          '#default_value' =>  $results ,
	   
	   
           );
        $form['step10field']['col9val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,
               '#default_value' =>  $total_fine ,

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           ); 


			$form['step10field']['submit_button']					= array(
																 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																'#type'					=>'submit',
																'#value'				=>!(trim($row_id)) ?  t(' Save ') : t(' Update ') ,
																);

			
		 
	
	 	
		$output1='';

    //print $previous_from_year_dt."sss".$previous_to_year_dt."sss".$inspector_id;
    //exit;

    if(trim($filenumber)){
      //$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t9_10 where  annual_inspection_id = :anid ', array(':anid' => trim($filenumber)  ));

            $mr_pending_case_select_query = db_select('labour_factory_statcell_annual_report_t9_10', 'a');
       
           $mr_pending_case_select_query->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
           $mr_pending_case_select_query->condition('b.inspector_id',trim($inspector_id),'=');
           $mr_pending_case_select_query->condition('b.report_from_date',trim($previous_from_year_dt),'>=');
           $mr_pending_case_select_query->condition('b.report_to_date',trim($previous_to_year_dt),'<=');
           $mr_pending_case_select_query->condition('a.results','PENDING','=');
           $mr_pending_case_select_query->condition('a.is_disabled', 0 ,'=');

            $mr_pending_case_select_query->fields('a',array('row_id','factory_name','factory_address',
        'reg_unreg','person_prosecuted','case_number','court_name','violation_description','results','total_fine'));

             $mr_pending_case_select_query->fields('b',array('annual_inspection_id'));

            $mr_pending_case_select_query_result = $mr_pending_case_select_query->execute();




      if($mr_pending_case_select_query_result->rowCount() > 0) 
              { 
      $output1 = "<div class='table-responsive'>
			   <table class='table table-striped table-bordered table-responsive add-employee-table-view'><thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory </th>
	    <th >Address of <br>the factory </th>
       
		 <th >Registered/un-registered <br>factory</th>

		 <th >Persons against whom <br>launched (Occupier, Manager etc.)</th>
       
		 <th >Case Number	</th>
		  <th >Name of Court	</th>
		  <th >Sections/Rules violated <br>with a short description	</th>
		   <th >Result	</th>
		  <th >Amount of fines	</th>
		   <th >EDIT</th>
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($mr_pending_case_select_query_result as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name; 
			  $factory_address=$squan->factory_address;     
			  $reg_unreg=$squan->reg_unreg;   
              $person_prosecuted=$squan->person_prosecuted; 
              $case_number=$squan->case_number;  

             // $case_number=$squan->case_number; 
              $court_name=$squan->court_name;  
              $violation_description=$squan->violation_description; 
              $results=$squan->results; 
              $total_fine=$squan->total_fine; 
             // $is_pending=$squan->is_pending; 
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab10-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		     // $img=  '<img  src="'.$base_root.$base_path.'/sites/all/themes/jackson/images/icon_delete.png" alt="Delete" title="Delete">';
		
		
		
		      $del_preper=l(t('Delete'),$bb ,array('html'=>TRUE)) ;
			  

			  $cc=$base_root.$base_path.'admin/annual-report/step10/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
		    
		
		
		
		      $edit_link=l(t('Edit'),$cc ,array('html'=>TRUE)) ;

              


			  
			  
              if($i%2==0){
		        $output1 .= "";
				 }
				else
				{
				$output1 .= "";
				}
				$output1.= "<td>".$i."</td>"; 
				$output1.= "<td>".$factory_name."</td>";
			    $output1.= "<td>".$factory_address."</td>";
                $output1.= "<td>".$reg_unreg."</td>";
                $output1.= "<td>".$person_prosecuted."</td>";
                $output1.= "<td>".$case_number."</td>";
                $output1.= "<td>".$court_name."</td>";
                $output1.= "<td>".$violation_description."</td>";
                $output1.= "<td>".$results."</td>";
                $output1.= "<td>".$total_fine."</td>";
                 $output1.= "<td>".$edit_link."</td>";
                $output1.= "<td >".$del_preper."</td>";
			
				
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table></div>"; 
			  
			

	
	   }
	}
	 $form['step10field']['prpersonlist'] = array(
	 	'#prefix' => '<div align="left" id="pr_officer_add">'.$output1,
		'#suffix' => '</div>',
       
	);
		
 
		
				
	
														
														  
	        return $form; 
  }


function step10_row_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=   encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=   encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
   

     $query_update_A = db_update('labour_factory_statcell_annual_report_t9_10');
      $query_update_A->fields(array(
       'is_disabled' => 1));
                    
                    
                    
       $query_update_A->condition('annual_inspection_id',trim($filenumber));
       $query_update_A->condition('row_id',trim($rowid));
       $query_update_A->execute();







	
	
	$message = '   delete is successfull ';
	
}
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$message = '    row is not  delete ';
     }	
	
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/annual-report/step10/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }



function annual_report_step10_submit($form , $form_state) {	

                global $base_root, $base_path,$full_base;

 $full_base='';


$val=$form_state['values'];
//print_r($val);
//exit;


    $inspectionid=trim($val['inspectionid']);
    $rowid=trim($val['rowid']);
    //part A
	$col1val=trim($val['col1val']); 
	$col2val=trim($val['col2val']); 
	$col3val=trim($val['col3val']); 
	$col4val=trim($val['col4val']); 
    $col5val=trim($val['col5val']); 
	
	$col6val=trim($val['col6val']); 
	$col7val=trim($val['col7val']); 
	$col8val=trim($val['col8val']); 

	$col9val=trim($val['col9val']); if(!$col9val)  $col9val= NULL;   
   


 $txn = db_transaction();
	  try {
        
          if($rowid){
        $query_update_a_yes=db_query('select  * from labour_factory_statcell_annual_report_t9_10 where  annual_inspection_id = :filenumber and row_id = :rid', array(':filenumber' => $inspectionid, ':rid' => $rowid));

             

             
		
	     if($query_update_a_yes->rowCount() > 0 ) {
       
         $query_update_B = db_update('labour_factory_statcell_annual_report_t9_10');
      $query_update_B->fields(array(
		   'factory_name' =>$col1val, 'factory_address' => $col2val, 'reg_unreg' => $col3val, 'person_prosecuted' => $col4val, 'case_number' => $col5val, 'court_name' => $col6val, 'violation_description' => $col7val
                         , 'results' => $col8val, 'total_fine' => $col9val ));
										
										
										
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->condition('row_id',$rowid);
       $query_update_B->execute(); 
        

        $message = 'DATA  UPDATE  SUCCESSFULLY  . ';

	      }
	      else
	      {
            $message = 'DATA  NOT UPDATE    . ';
	      }
          
          }
	      else
	      {

    $maxresult=db_query('select  max(row_id) maxsl from labour_factory_statcell_annual_report_t9_10');	
	        $result=$maxresult->fetchAssoc();
	        $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1;	}else{ $querystring=$max_sl_number+1; }
		    $autoGENNO=$querystring;
    


  $fieldsE = array('row_id' => $autoGENNO, 'annual_inspection_id' =>$inspectionid,'factory_name' =>$col1val, 'factory_address' => $col2val, 'reg_unreg' => $col3val, 'person_prosecuted' => $col4val, 'case_number' => $col5val, 'court_name' => $col6val, 'violation_description' => $col7val
                         , 'results' => $col8val, 'total_fine' => $col9val, 'is_pending' => 1);
		  
		   
                      db_insert('labour_factory_statcell_annual_report_t9_10')->fields($fieldsE)->execute();

                       

                         $message = 'DATA  SAVED  SUCCESSFULLY  . ';
                      }
				 
	           
	              drupal_set_message(t($message));
				       //$full_base=$base_root.$base_path.'admin/annual-report/'.encryption_decryption_fun('encrypt',$autoGENNO);
				 
	           $full_base=$base_root.$base_path.'admin/annual-report/step10/'.encryption_decryption_fun('encrypt',$inspectionid);
	             drupal_goto($full_base);



     }
	catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/annual-report/step10/'.encryption_decryption_fun('encrypt',$inspectionid);

             $message = 'DATA  NOT SAVED  . ';
                      
		   
                      drupal_set_message(t($message));
	           
	             drupal_goto($full_base);
	
     }	
     
     }   