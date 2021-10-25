<?php
function month_report_step14( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

   $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

      drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/formcheck.js');
      drupal_add_js(drupal_get_path('module', 'caf_form') . '/js/myfunction.js');

      $get_info_montly_report=get_monthly_area_from_to_date($filenumber);

    $form['step14field'] = array(
          '#title' => t('<font color="DarkGreen">'.$get_info_montly_report.'<b>    </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

$form['step14field']['monthlyformid'] = 
         array('#type' => 'hidden',  
         '#value' => $filenumber,
     
        );
         $step14_select_query = db_select('labour_factory_statcell_form_5_t14_6_t6_7_t8', 'a');
       
        $step14_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step14_select_query->fields('a',array('no_of_units_visit',
    'no_of_visit_paid_general' ,
    'no_of_visit_paid_complaint' ,
    'no_of_visit_paid_accident',
    'no_of_complaints_received' ,
    'details_of_complaint',
    'no_of_accidents_reported' ,
    'accident_details_name_of_deceased' ,
    'accident_details_age' ,
    'accident_details_sex' ,
    'accident_details_date_of_accident',
    'accident_details_nature_of_accident' ,
    'accident_details_description' ,
    'accident_details_place' ,
    'accident_details_name_of_employer' ,
    'accident_details_address_of_site' ,
    'details_of_violation_general_visit' ,
    'no_of_prosecution_general_visit',
    'no_of_prosecution_complaint' ,
    'no_of_prosecution_accident' ,
    'details_of_prosecution_violation' ,
    'details_of_prosecution_court_name',
    'details_of_prosecution_case_no' ,
    'details_of_prosecution_result' ,
    'other_information' ));
    $step14_select_query_result = $step14_select_query->execute(); 
    
    $result_step14=$step14_select_query_result->fetchAssoc();

     $form['step14field']['one'] = array
              (
           '#prefix' => '<table    ><tr><td   >', 
           '#markup'=>'<b> 1 &nbsp; &nbsp; No. of Units visited  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['oneValue'] = array
              (
           '#prefix' => '<td       >', 
           '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
          '#default_value' =>$result_step14['no_of_units_visit']
     
     
           );


            $form['step14field']['twohead'] = array
              (
           '#prefix' => '<tr><td colspan="2"   >', 
           '#markup'=>'<b> 2 &nbsp; &nbsp; No. of visits paid  </b>',

              '#suffix'=>'</td></tr>',

     
     
           ); 


            $form['step14field']['twoone'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b> a) &nbsp; &nbsp; for general  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['twooneValue'] = array
              (
           '#prefix' => '<td >', 
           '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['no_of_visit_paid_general']
     
     
           );

    $form['step14field']['twotwo'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  b) &nbsp; &nbsp; for complaint  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['twotwoValue'] = array
              (
           '#prefix' => '<td >', 
           '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['no_of_visit_paid_complaint']
     
     
           );

          $form['step14field']['twothree'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  c) &nbsp; &nbsp; for accident  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['twothreeValue'] = array
              (
           '#prefix' => '<td >', 
           '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
            '#default_value' =>$result_step14['no_of_visit_paid_accident']
     
     
           );

           $form['step14field']['three'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  3) &nbsp; &nbsp; No. of complains received  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['threeValue'] = array
              (
           '#prefix' => '<td >', 
           '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['no_of_complaints_received']
     
     
           );

           $form['step14field']['four'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  4 &nbsp; &nbsp; Details of the complaint with violation, if any  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['fourValue'] = array
              (
           '#prefix' => '<td >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

          '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step14['details_of_complaint']
     
     
           );

           $form['step14field']['five'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  5 &nbsp; &nbsp;No. of accidents reported  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['fiveValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['no_of_accidents_reported']
     
     
           );
            $form['step14field']['sixhead'] = array
              (
           '#prefix' => '<tr><td colspan="2"   >', 
           '#markup'=>'<b> 6 &nbsp; &nbsp;  Details of accident  </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

             $form['step14field']['sixone'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  a)  &nbsp; &nbsp;  Name of I.P/deceased  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['accident_details_name_of_deceased']
     
     
           );

           $form['step14field']['sixtwo'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  b)  Age </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixtwoValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step14['accident_details_age']
     
     
           );

            $form['step14field']['sixthree'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  c)  Sex </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixthreeValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
               '#default_value' =>$result_step14['accident_details_sex']
     
     
           );

           $form['step14field']['sixtfour'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  d)  Dt. & time of accident </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixfourValue'] = array
              (
           '#prefix' => '<td >', 
         
          '#type' => 'textfield',
            '#size' => 12,
            '#attributes' => array('class' => array('datepicker_retify')),

          '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step14['accident_details_date_of_accident']
     
     
           );

 $form['step14field']['sixfive'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    e) Nature of accident (serious/Fatal) </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixfiveValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['accident_details_nature_of_accident']
     
     
           );


           $form['step14field']['sixsix'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>   f. Brief description of accident with violation, if any </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixsixValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,
             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td></tr>',
          '#default_value' =>$result_step14['accident_details_description']
     
     
           );


           $form['step14field']['sixeight'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>      g)  Place of accident </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixeightValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,
             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step14['accident_details_place']
     
     
           );

           $form['step14field']['sixnine'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>        h)  Name of employer </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       $form['step14field']['sixnineValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,
             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td></tr>',
           '#default_value' =>$result_step14['accident_details_name_of_employer']
     
     
           );

$form['step14field']['sixten'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>     i)  Address of the site </b>',

              '#suffix'=>'</td>',

     
     
           ); 

       $form['step14field']['sixtenValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,

             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td></tr>',
               '#default_value' =>$result_step14['accident_details_address_of_site']
     
     
           );

      
$form['step14field']['seven'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    7    Details of violation in general visit (S/R) </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
$form['step14field']['sevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step14['details_of_violation_general_visit']
     
     
           ); 
$form['step14field']['eighthead'] = array
              (
           '#prefix' => '<tr><td colspan="2"   >', 
           '#markup'=>'<b>    8  No. of prosecution </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 
        
          
           $form['step14field']['eightone'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    a)  In connection with general visit </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
   $form['step14field']['eightoneValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
                 '#default_value' =>$result_step14['no_of_prosecution_general_visit']
     
     
           ); 


       $form['step14field']['eighttwo'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    b)  In connection with complaint enquiry </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
   $form['step14field']['eighttwoValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
            '#default_value' =>$result_step14['no_of_prosecution_complaint']
     
     
           ); 


            $form['step14field']['eightthree'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    c)  In connection with accident enquiry </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
       $form['step14field']['eightthreeValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
            '#default_value' =>$result_step14['no_of_prosecution_accident']
     
     
           ); 
            $form['step14field']['ninehead'] = array
              (
           '#prefix' => '<tr><td colspan="2"   >', 
           '#markup'=>'<b>   9.  Details of prosecution against whom launched </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

            $form['step14field']['nineone'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    a)  Violation (S/R) </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
       $form['step14field']['nineoneValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step14['details_of_prosecution_violation']
     
     
           );

            $form['step14field']['ninetwo'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    b)  Name of the Court </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
       $form['step14field']['ninetwoValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
             '#default_value' =>$result_step14['details_of_prosecution_court_name']
     
     
           );

            $form['step14field']['ninethree'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>      c)  Case No </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
       $form['step14field']['ninethreeValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step14['details_of_prosecution_case_no']
     
     
           );

            $form['step14field']['ninefour'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>         d)  Result / Remarks </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
       $form['step14field']['ninefourValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step14['details_of_prosecution_result']
     
     
           );

 $form['step14field']['ten'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b> 10)   Any other information </b>',

              '#suffix'=>'</td>',
     
     
           ); 
            $form['step14field']['tenValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 5,

            '#suffix'=>'</td></tr></table>',
              '#default_value' =>$result_step14['other_information']
     
     
           );
          
     

      
           
            $form['step14field']['submit_button']          = array(
                                 
                               '#prefix' => '<div style="text-align:center;" >',
                                '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save ')
                                );

           return $form;
         }

      function month_report_step14_submit($form , $form_state) { 


         global $base_root, $base_path,$full_base;




   $val=$form_state['values'];

 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

  $onevalue=trim($val['oneValue']);  if(!$onevalue) $onevalue= NULL;    
  //print   "ssss".trim($val['onevalue']);
  //exit;   
  $twooneValue=trim($val['twooneValue']); if(!$twooneValue) $twooneValue= NULL;
  $twotwoValue=trim($val['twotwoValue']); if(!$twotwoValue) $twotwoValue= NULL;
  $twothreeValue=trim($val['twothreeValue']); if(!$twothreeValue) $twothreeValue= NULL;
  $threeValue=trim($val['threeValue']); if(!$threeValue) $threeValue= NULL;


  $fourValue=trim($val['fourValue']);  if(!$fourValue) $fourValue= NULL;         
  $fiveValue=trim($val['fiveValue']); if(!$fiveValue) $fiveValue= NULL;
  $sixValue=trim($val['sixValue']); if(!$sixValue) $sixValue= NULL;
  $sixtwoValue=trim($val['sixtwoValue']); if(!$sixtwoValue) $sixtwoValue= NULL;
  $sixthreeValue=trim($val['sixthreeValue']); if(!$sixthreeValue) $sixthreeValue= NULL;


  $sixfourValue=trim($val['sixfourValue']); if(!$sixfourValue) $sixfourValue= NULL;
  $sixfiveValue=trim($val['sixfiveValue']); if(!$sixfiveValue) $sixfiveValue= NULL;
  $sixsixValue=trim($val['sixsixValue']); if(!$sixsixValue) $sixsixValue= NULL;
  //$sixsevenValue=trim($val['sixsevenValue']); if(!$sixsevenValue) $sixsevenValue= NULL;
  $sixeightValue=trim($val['sixeightValue']); if(!$sixeightValue) $sixeightValue= NULL;


  $sixnineValue=trim($val['sixnineValue']); if(!$sixnineValue) $sixnineValue= NULL;
  $sixtenValue=trim($val['sixtenValue']); if(!$sixtenValue) $sixtenValue= NULL;
  $sevenvalue=trim($val['sevenvalue']); if(!$sevenvalue) $sevenvalue= NULL;
  $eightoneValue=trim($val['eightoneValue']); if(!$eightoneValue) $eightoneValue= NULL;
  $eighttwoValue=trim($val['eighttwoValue']); if(!$eighttwoValue) $eighttwoValue= NULL;


  $eightthreeValue=trim($val['eightthreeValue']); if(!$eightthreeValue) $eightthreeValue= NULL;
  $nineoneValue=trim($val['nineoneValue']); if(!$nineoneValue) $nineoneValue= NULL;
  $ninetwoValue=trim($val['ninetwoValue']); if(!$ninetwoValue) $ninetwoValue= NULL;
  $ninethreeValue=trim($val['ninethreeValue']); if(!$ninethreeValue) $ninethreeValue= NULL;
  $ninefourValue=trim($val['ninefourValue']); if(!$ninefourValue) $ninefourValue= NULL;
  $tenValue=trim($val['tenValue']); if(!$tenValue) $tenValue= NULL;
  

  $txn = db_transaction();
    try {



            $query_update_yes=db_query('select  * from labour_factory_statcell_form_5_t14_6_t6_7_t8 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
       if($query_update_yes->rowCount() > 0) 
          {
         $query_update_A = db_update('labour_factory_statcell_form_5_t14_6_t6_7_t8');
        $query_update_A->fields(array(
     'no_of_units_visit'=> $onevalue , 'no_of_visit_paid_general' =>$twooneValue,  'no_of_visit_paid_complaint' =>$twotwoValue,'no_of_visit_paid_accident' =>$twothreeValue, 'no_of_complaints_received' => $threeValue, 'details_of_complaint' => $fourValue,  'no_of_accidents_reported' => $fiveValue, 'accident_details_name_of_deceased' => $sixValue, 'accident_details_age' => $sixtwoValue, 'accident_details_sex' => $sixthreeValue, 'accident_details_date_of_accident' => $sixfourValue, 'accident_details_nature_of_accident' => $sixfiveValue, 'accident_details_description' => $sixsixValue, 'accident_details_place' => $sixeightValue, 'accident_details_name_of_employer' => $sixnineValue
      , 'accident_details_address_of_site' => $sixtenValue, 'details_of_violation_general_visit' => $sevenvalue,  'no_of_prosecution_general_visit' => $eightoneValue,'no_of_prosecution_complaint' => $eighttwoValue

      , 'no_of_prosecution_accident' => $eightthreeValue, 'details_of_prosecution_violation' => $nineoneValue, 'details_of_prosecution_court_name' => $ninetwoValue
      , 'details_of_prosecution_case_no' => $ninethreeValue, 'details_of_prosecution_result' => $ninefourValue, 'other_information' => $tenValue


   ));
                    
                    
                    
       $query_update_A->condition('monthly_form_id',$monthly_form_id);
       $query_update_A->execute(); 

          }
          else
          {

          $maxresult=db_query('select  max(bocw_id) maxsl from labour_factory_statcell_form_5_t14_6_t6_7_t8'); 
          $result=$maxresult->fetchAssoc();
          $max_sl_number = trim($result['maxsl']); 
          if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
          $rowid=$querystring;



          

       $fieldsA = array('bocw_id' => $rowid ,'monthly_form_id' => $monthly_form_id,'form_type' => 'GENERAL', 'no_of_units_visit'=> $onevalue , 'no_of_visit_paid_general' =>$twooneValue,  'no_of_visit_paid_complaint' =>$twotwoValue,'no_of_visit_paid_accident' =>$twothreeValue, 'no_of_complaints_received' => $threeValue, 'details_of_complaint' => $fourValue,  'no_of_accidents_reported' => $fiveValue, 'accident_details_name_of_deceased' => $sixValue, 'accident_details_age' => $sixtwoValue, 'accident_details_sex' => $sixthreeValue, 'accident_details_date_of_accident' => $sixfourValue, 'accident_details_nature_of_accident' => $sixfiveValue, 'accident_details_description' => $sixsixValue, 'accident_details_place' => $sixeightValue, 'accident_details_name_of_employer' => $sixnineValue
      , 'accident_details_address_of_site' => $sixtenValue, 'details_of_violation_general_visit' => $sevenvalue,  'no_of_prosecution_general_visit' => $eightoneValue,'no_of_prosecution_complaint' => $eighttwoValue

      , 'no_of_prosecution_accident' => $eightthreeValue, 'details_of_prosecution_violation' => $nineoneValue, 'details_of_prosecution_court_name' => $ninetwoValue
      , 'details_of_prosecution_case_no' => $ninethreeValue, 'details_of_prosecution_result' => $ninefourValue, 'other_information' => $tenValue


       );

             db_insert('labour_factory_statcell_form_5_t14_6_t6_7_t8')->fields($fieldsA)->execute(); 

              }


   

          

               $full_base=$base_root.$base_path.'admin/monthly-report/step14/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

              }
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);

    $full_base=$base_root.$base_path.'admin/monthly-report/step14/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA NOT SAVED   . ';
                      
       
            drupal_set_message(t($message));
             
          drupal_goto($full_base);
  
     }
   }



     

           ?>