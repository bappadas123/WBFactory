<?php

function annual_report_step6( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;
	 
	
	 $filenumber=encryption_decryption_fun('decrypt',$filenumber);
	
	
	 
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
		
	      $form['step6Afield'] = array(
          '#title' => t('<b> Area:'.$area.' , From date: '.$report_from_date.' , To date: '.$report_to_date.'</b>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
          
      $form['step6Afield']['inspectionid'] = 
	    array('#type' => 'hidden',  
	    '#value' => $filenumber,
	   
	   );
		
     	
$form['step6Afield']['colA1'] = array

              (
		       '#prefix' => '<div class="table-panel-header"><b> 6.A. Welfare Officer and Safety Officer.</b></div><div class="table-responsive"><table  class="table" border="1">
			   <tr><td rowspan="2"   >', 
		       '#markup'=>'<b> Name of the Factory  </b>',

		          '#suffix'=>'</td>',
	   
	   
           );


                $form['step6Afield']['colA2'] = array
              (
		       '#prefix' => ' <td colspan="2"   >', 
		        '#markup'=>'<b> Number required to be appointed under the statute  </b>',
           

		        '#suffix'=>'</td>',
	   
	   
           ); 


               $form['step6Afield']['colA3'] = array
              (
		       '#prefix' => ' <td colspan="2"  >', 
		        '#markup'=>'<b> Actually appointed  </b>',
           

		        '#suffix'=>'</td></tr>',
	   
	   
           ); 

            $form['step6Afield']['colA21'] = array
              (
		       '#prefix' => '<tr><td  >', 
		         '#markup'=>'<b> Welfare Officer  </b>',
		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step6Afield']['colA22'] = array
              (
		       '#prefix' => '<td  >', 
		         '#markup'=>'<b> Safety Officer  </b>',
		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step6Afield']['colA31'] = array
              (
		       '#prefix' => '<td  >', 
		         '#markup'=>'<b> Welfare Officer   </b>',
		          '#suffix'=>'</td>',
	   
	   
           );

               $form['step6Afield']['colA32'] = array
              (
		       '#prefix' => '<td  >', 
		         '#markup'=>'<b> Safety Officer  </b>',
		          '#suffix'=>'</td></tr>',
	   
	   
           );

              $form['step6Afield']['colA1val'] = array
              (
		       '#prefix' => '<tr><td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 3,
                 '#cols' => 3,
		          '#suffix'=>'</td>',
	   
	   
           );


              

     


            
              $form['step6Afield']['colA2val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step6Afield']['colA22val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step6Afield']['colA31val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td>',
	   
	   
           );

               $form['step6Afield']['colA32val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textfield',
                '#size' => 5,

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           );

             

 


 

        

			$form['step6Afield']['submit_button']					= array(
																 
                                                               

																 '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																 '#type' => 'button',
		                                                         '#event' => 'click',

															  '#default_value' => 'Add   ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step6_officer_data',
                                                              'wrapper' => 'pr_officer_add',
                                                               'method' => 'html',
                                                               'effect' => 'fade'
                                                               )
																);


     $output1='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t6_a where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
      $output1 = "<div class='table-responsive'><table class='table table-striped table-bordered table-responsive add-employee-table-view'>
	  <thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory </th>
	    <th >Welfare Officer </th>
       
		 <th >Safety Officer</th>

		 <th >Welfare Officer</th>
       
		 <th >Safety Officer	</th>
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name; 
			  $welfare_officer_required=$squan->welfare_officer_required;     
			  $safety_officer_required=$squan->safety_officer_required;   
              $welfare_officer_appointed=$squan->welfare_officer_appointed; 
              $safety_officer_appointed=$squan->safety_officer_appointed;   
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab6-parta-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
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
				$output1.= "<td>".$factory_name."</td>";
			    $output1.= "<td>".$welfare_officer_required."</td>";
                $output1.= "<td>".$safety_officer_required."</td>";
                $output1.= "<td>".$welfare_officer_appointed."</td>";
                $output1.= "<td>".$safety_officer_appointed."</td>";
			
				$output1.= "<td >".$del_preper."</td>";
			
              
			   $output1 .= "</tr>";
	          }
              $output1 .= "</table></div>"; 
			  
			

	
	   }
	}
	 $form['step1Dfield']['prpersonlist'] = array(
	 	'#prefix' => '<div align="left" id="pr_officer_add">'.$output1,
		'#suffix' => '</div>',
       
	);

		 
		 
	// Part B
	 	
	
     $form['step6Bfield'] = array(
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

		
     	
$form['step6Bfield']['colB1'] = array
              (
		       '#prefix' => '<div class="table-panel-header"><b>6(B) Details of Safety policy and safety committee</b></div><div class="table-responsive"><table class="table table-striped table-bordered table-responsive"><thead><tr><th >', 
		       '#markup'=>'<b> Name of the factory having safety committees.  </b>',

		          '#suffix'=>'</th>',
	   
	   
           );


                $form['step6Bfield']['colB2'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Address of the factory  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 


               $form['step6Bfield']['colB3'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> How the Committee has been set up?( By nomination/election).  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

            $form['step6Bfield']['colB4'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> Whether any Safety policy has been framed by the <br> factory with respect to health and safety of the workers  </b>',
           

		        '#suffix'=>'</th>',
	   
	   
           ); 

           $form['step6Bfield']['colB5'] = array
              (
		       '#prefix' => ' <th>', 
		        '#markup'=>'<b> if, so has it been submitted to chief inspector <br> of factories, West Bengal?  </b>',
           

		        '#suffix'=>'</th></tr></thead>',
	   
	   
           ); 

           

              $form['step6Bfield']['colB1val'] = array
              (
		       '#prefix' => '<tr><td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 3,
                 '#cols' => 3,
		          '#suffix'=>'</td>',
	   
	   
           );

       $form['step6Bfield']['colB2val'] = array
              (
		       '#prefix' => '<td  >', 
		         '#type' => 'textarea',
		       
                '#rows' => 3,
                 '#cols' => 3,
		          '#suffix'=>'</td>',
	   
	   
           );
              

          $form['commity_option'] = array(
	     '#type' => 'value',
         //'#value' => array('0'=>t('select'),'1'=>t('Male(M)'),'2'=>t('Female(F)'),'3'=>t('Transgender'))
		   '#value' => array('0'=>t('select  '),'Nomination'=>t('Nomination'),'Election'=>t('Election'))
		
         );
	
	
	


            
              $form['step6Bfield']['colB3val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'select',
              '#options' => $form['commity_option']['#value'],

		        '#suffix'=>'</td>',
	   
	   
           );

              

               $form['step6Bfield']['colB4val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 3,
                 '#cols' => 3,

		        '#suffix'=>'</td>',
	   
	   
           );

             
       
               $form['step6Bfield']['colB5val'] = array
              (
		       '#prefix' => ' <td  >', 
		       '#type' => 'textarea',
		       
                '#rows' => 3,
                 '#cols' => 3,

		        '#suffix'=>'</td></tr></table></div>',
	   
	   
           );
 


 

        

			$form['step6Bfield']['submit_button_2']					= array(
																 
                                                               
                                                                 '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
																 '#type' => 'button',
		                                                         '#event' => 'click',

															  '#default_value' => 'Add factory  ',
                                                              '#ajax' => array(
                                                              'callback' => 'add_step6_committees_data',
                                                              'wrapper' => 'pr_committes_add',
                                                               'method' => 'html',
                                                               'effect' => 'fade'
                                                               )


																);

		
     $output2='';
      if(trim($filenumber)){
      $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t6_b where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_1_c->rowCount() > 0) 
              { 
      $output2 = "<div class='table-responsive'><table class='table table-striped table-bordered table-responsive add-employee-table-view'>
	  <thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory </th>
	    <th >Address </th>
       
		 <th >nomination/election</th>

		 <th >Whether any Safety policy <br> has been framed by the factory with respect <br> to health and safety of the workers</th>
       
		 <th >if, so has it been submitted to <br> chief inspector of factories, West Bengal?	</th>
		 
		 <th >DELETE</th>
		</tr></thead>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name; 
			  $factory_address=$squan->factory_address;     
			  $committee_setup=$squan->committee_setup;   
              $safety_policy=$squan->safety_policy; 
              $is_submitted_to_cif=$squan->is_submitted_to_cif;   
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab6-partb-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
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
				$output2.= "<td>".$factory_name."</td>";
			    $output2.= "<td>".$factory_address."</td>";
                $output2.= "<td>".$committee_setup."</td>";
                $output2.= "<td>".$safety_policy."</td>";
                $output2.= "<td>".$is_submitted_to_cif."</td>";
			
				$output2.= "<td >".$del_preper."</td>";
			
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table></div>"; 
			  
			

	
	   }
	}
	 $form['step6Bfield']['prpersonlist_two'] = array(
	 	'#prefix' => '<div align="left" id="pr_committes_add">'.$output2,
		'#suffix' => '</div>',
       
	);
		
				
	
														
														  
	        return $form; 
  }



 function step6_parta_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t6_a')
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

      $aa=$base_root.$base_path.'admin/annual-report/step6/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }



function add_step6_officer_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colA1val=trim($val['colA1val']);     
      $colA2val=trim($val['colA2val']);     if(!$colA2val)   $colA2val= NULL;  
      $colA22val=trim($val['colA22val']);   if(!$colA22val)   $colA22val= NULL;  
      $colA31val=trim($val['colA31val']);   if(!$colA31val)   $colA31val= NULL;  
      $colA32val=trim($val['colA32val']);   if(!$colA32val)   $colA32val= NULL;  
     


   if(!$colA1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   name <b>    </font>";
	  exit;
	 } 

	 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t6_a ');
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
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'factory_name' =>$colA1val ,'welfare_officer_required' =>$colA2val,'safety_officer_required' =>$colA22val, 'welfare_officer_appointed' => $colA31val, 'safety_officer_appointed' => $colA32val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_t6_a')->fields($fieldsE)->execute();	
	 
	 
	$query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t6_a where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
    
      $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory </th>
	    <th >Welfare Officer </th>
       
		 <th >Safety Officer</th>

		 <th >Welfare Officer</th>
       
		 <th >Safety Officer	</th>
		 
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name; 
			  $welfare_officer_required=$squan->welfare_officer_required;     
			  $safety_officer_required=$squan->safety_officer_required;   
              $welfare_officer_appointed=$squan->welfare_officer_appointed; 
              $safety_officer_appointed=$squan->safety_officer_appointed;   
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab6-partb-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
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
				$output1.= "<td>".$factory_name."</td>";
			    $output1.= "<td>".$welfare_officer_required."</td>";
                $output1.= "<td>".$safety_officer_required."</td>";
                $output1.= "<td>".$welfare_officer_appointed."</td>";
                $output1.= "<td>".$safety_officer_appointed."</td>";
			
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


     function step6_partb_del(  $filenumber = NULL , $rowid = NULL){
	  
	 global $base_root, $base_path;
	  //  $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));
	   
      //$tyinfg= encryption_decryption_fun('decrypt', trim($tyinfg));

	   $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
	   
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
	   
	$txn = db_transaction();
	  try {
		  
    db_delete('labour_factory_statcell_annual_report_t6_b')
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

      $aa=$base_root.$base_path.'admin/annual-report/step6/'.encryption_decryption_fun('encrypt',$filenumber);
     drupal_set_message(t($message));
		 
		  drupal_goto($aa);
		  
  }                     


  function add_step6_committees_data($form , $form_state) {	
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $inspectionid=trim($val['inspectionid']);
      $colB1val=trim($val['colB1val']);     
      $colB2val=trim($val['colB2val']);     
      $colB3val=trim($val['colB3val']);    
      $colB4val=trim($val['colB4val']);    
      $colB5val=trim($val['colB5val']);   
     


   if(!$colB1val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please enter   name <b>    </font>";
	  exit;
	 } 

	 if(!$colB3val)
	 {
	  drupal_get_messages(error);
	  return "<font color='#FF3333'><b>please select how committee setup  <b>    </font>";
	  exit;
	 }

	 
	    


     $txn = db_transaction();

        try {
     
	 
	  $ins_pr_person=db_query('select  max(row_id) ownermax from labour_factory_statcell_annual_report_t6_b ');
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
			
	      
		   
		    $fieldsE = array('row_id' => $count_profile, 'annual_inspection_id' => $inspectionid,'factory_name' =>$colB1val ,'factory_address' =>$colB2val,'committee_setup' =>$colB3val, 'safety_policy' => $colB4val, 'is_submitted_to_cif' => $colB5val);
		  
		   
           db_insert('labour_factory_statcell_annual_report_t6_b')->fields($fieldsE)->execute();	
	 
	 
	
    
       $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t6_b where  annual_inspection_id = :anid', array(':anid' => trim($inspectionid) ));
      
      $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the Factory </th>
	    <th >Address </th>
       
		 <th >nomination/election</th>

		 <th >Whether any Safety policy has been framed <br>by the factory with respect to health <br>and safety of the workers</th>
       
		 <th >if, so has it been submitted to chief <br>inspector of factories, West Bengal?	</th>
		 
		 <th >DELETE</th>
		</tr>";  
			  $i=0;
		foreach($query_tab_1_c as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $annual_inspection_id = $squan->annual_inspection_id; 
	          $factory_name=$squan->factory_name; 
			  $factory_address=$squan->factory_address;     
			  $committee_setup=$squan->committee_setup;   
              $safety_policy=$squan->safety_policy; 
              $is_submitted_to_cif=$squan->is_submitted_to_cif;   
            
              
			 //  $bb=$base_root.$base_path.'equalremuins/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id).'/presentperdel';

			   $bb=$base_root.$base_path.'admin/annual-report-tab6-partb-del/'.encryption_decryption_fun('encrypt',$annual_inspection_id).'/'.encryption_decryption_fun('encrypt',$row_id);
      
		
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
				$output2.= "<td>".$factory_name."</td>";
			    $output2.= "<td>".$factory_address."</td>";
                $output2.= "<td>".$committee_setup."</td>";
                $output2.= "<td>".$safety_policy."</td>";
                $output2.= "<td>".$is_submitted_to_cif."</td>";
			
				$output2.= "<td >".$del_preper."</td>";
			
              
			   $output2 .= "</tr>";
	          }
              $output2 .= "</table>";  
			  
			

	
	   



	  }
  catch (Exception $e) {
    $form_state['rebuild'] = TRUE;
 
    $txn->rollback();
  
    watchdog_exception('type', $e);
	$output1 = ' DATA NOT INSERT'.$inspectionid;
  }  
	


                          drupal_get_messages(error);
		                  return $output2;
		                  exit;
                          
                          }