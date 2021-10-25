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
          '#default_value' =>$result_step14['no_of_units_visit'] ,
           '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
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
           '#default_value' =>$result_step14['no_of_visit_paid_general'] ,
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
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
           '#default_value' =>$result_step14['no_of_visit_paid_complaint'] ,
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
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
            '#default_value' =>$result_step14['no_of_visit_paid_accident'] ,
             '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
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
           '#default_value' =>$result_step14['no_of_complaints_received'] ,
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
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
           '#default_value' =>$result_step14['no_of_accidents_reported'] ,
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           );
$form['step14field']['ten'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>  Any other information </b>',

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
                                '#value'        =>t(' Save '),
                               '#submit' => array('month_report_step14_parta_save'),
                                );

      $form['step14sixfield'] = array
              (
           

            '#title' => t('<font color="DarkGreen"><b>  6 &nbsp; &nbsp;  Details of accident   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
     
     
           ); 

             $form['step14sixfield']['sixone'] = array
              (
           '#prefix' => '<table class="table"> <tr><td   >', 
           '#markup'=>'<b>  a)  &nbsp; &nbsp;  Name of I.P/deceased  </b>',

              '#suffix'=>'</td>',
     
     
           ); 

               $form['step14sixfield']['sixtwo'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>  b)  Age </b>',

              '#suffix'=>'</td>',
     
     
           ); 

       /**/

          

               $form['step14sixfield']['sixthree'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>  c)  Sex </b>',

              '#suffix'=>'</td>',
     
     
           ); 

              $form['step14sixfield']['sixtfour'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>  d)  Dt. & time of accident </b>',

              '#suffix'=>'</td>',
     
     
           );
              $form['step14sixfield']['sixfive'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>    e) Nature of accident (serious/Fatal) </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 

   $form['step14sixfield']['sixValue'] = array
              (
           '#prefix' => '<tr><td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td>',
          // '#default_value' =>$result_step14['accident_details_name_of_deceased']
     
     
           );


       $form['step14sixfield']['sixtwoValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td>',
              //'#default_value' =>$result_step14['accident_details_age']
     
     
           );

           
         $form['sex_option'] = array(
         '#type' => 'value',
         '#value' => array('male'=>t('Male'),'female'=>t('Female'))
     
    
         );
  
  
  


            
            
               

       $form['step14sixfield']['sixthreeValue'] = array
              (
           '#prefix' => '<td >', 
            '#type' => 'select',
              '#options' => $form['sex_option']['#value'],

          '#suffix'=>'</td>',
             //  '#default_value' =>$result_step14['accident_details_sex']
     
     
           );

            

       $form['step14sixfield']['sixfourValue'] = array
              (
           '#prefix' => '<td >', 
         
          '#type' => 'textfield',
            '#size' => 12,
            '#attributes' => array('class' => array('datepicker_retify')),

          '#suffix'=>'</td>',
            // '#default_value' =>$result_step14['accident_details_date_of_accident']
     
     
           );



       $form['step14sixfield']['sixfiveValue'] = array
              (
           '#prefix' => '<td >', 
          '#type' => 'textfield',
           '#size' => 5,

          '#suffix'=>'</td></tr>',
         //  '#default_value' =>$result_step14['accident_details_nature_of_accident']
     
     
           );


           $form['step14sixfield']['sixsix'] = array
              (
           '#prefix' => '<tr><td colspan="2"   >', 
           '#markup'=>'<b>   f. Brief description of accident with violation, if any </b>',

              '#suffix'=>'</td>',
     
     
           ); 

               $form['step14sixfield']['sixeight'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>      g)  Place of accident </b>',

              '#suffix'=>'</td>',
     
     
           ); 

              $form['step14sixfield']['sixnine'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>        h)  Name of employer </b>',

              '#suffix'=>'</td>',
     
     
           );

              $form['step14sixfield']['sixten'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>     i)  Address of the site </b>',

              '#suffix'=>'</td></tr>',

     
     
           );

       $form['step14sixfield']['sixsixValue'] = array
              (
           '#prefix' => '<tr><td colspan="2" >', 
         // '#type' => 'textfield',
         //  '#size' => 5,
             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td>',
         // '#default_value' =>$result_step14['accident_details_description']
     
     
           );


          

       $form['step14sixfield']['sixeightValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,
             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td>',
             //'#default_value' =>$result_step14['accident_details_place']
     
     
           );

            

       $form['step14sixfield']['sixnineValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,
             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td>',
          // '#default_value' =>$result_step14['accident_details_name_of_employer']
     
     
           );

 

       $form['step14sixfield']['sixtenValue'] = array
              (
           '#prefix' => '<td >', 
         // '#type' => 'textfield',
         //  '#size' => 5,

             '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,


          '#suffix'=>'</td></tr></table>',
          //     '#default_value' =>$result_step14['accident_details_address_of_site']
     
     
           );

         $form['step14sixfield']['submit_button']          = array(
                                 
                                '#prefix' => '<div style="text-align:center;" >',
                                '#suffix'=>'</div>', 
                              
                              
                               // '#submit' => array('mr_step4_parta_save'),
                               '#type' => 'button',
                              '#event' => 'click',

                              '#default_value' => 'ADD More  ',
                              '#ajax' => array(
                              'callback' => 'add_step14_part6',
                              'wrapper' => 'part14_6_div',
                              'method' => 'html',
                              'effect' => 'fade'
                               )

                                );


       

     $output2='';
      if(trim($filenumber)){
      $query_tab_14_6=db_query('select  *  from labour_factory_statcell_form_5_t14_6  where monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_14_6->rowCount() > 0) 
              { 
     $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      <th > SL NO</th>
       <th > Name of I.P/deceased (S/R)</th>
       <th > Age</th>
      
      <th >Sex</th>
       
     <th >Dt. & time of accident</th>

     <th >Nature of accident (serious/Fatal)</th>

   
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_14_6 as $squan) {
      $i++;
          $accident_id = $squan->accident_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $accident_details_name_of_deceased=$squan->accident_details_name_of_deceased;

          $accident_details_age=$squan->accident_details_age;
          $accident_details_sex=$squan->accident_details_sex;
          $accident_details_date_of_accident=$squan->accident_details_date_of_accident;

          $accident_details_nature_of_accident=$squan->accident_details_nature_of_accident;
          $accident_details_description=$squan->accident_details_description;
          $accident_details_place=$squan->accident_details_place;
          $accident_details_name_of_employer=$squan->accident_details_name_of_employer;
          $accident_details_address_of_site=$squan->accident_details_address_of_site;
       

              
              
              
      

          $bb=$base_root.$base_path.'admin/monthly-report-fourteen6del/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$accident_id);
      
    
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
                $output2.= "<td>".$accident_details_name_of_deceased."</td>";
                $output2.= "<td>".$squan->accident_details_age."</td>";
                $output2.= "<td>".$squan->accident_details_sex."</td>";
              

                 $output2.= "<td>".date('d-m-Y', strtotime($squan->accident_details_date_of_accident))."</td>";

                  $output2.= "<td>".$squan->accident_details_nature_of_accident."</td>";
                
                
                $output2.= "<td >".$del_preper."</td>";
      
              
              $output2 .= "</tr>";
            }
              $output2 .= "</table>";
        
      

  
     }
  }
   $form['step14sixfield']['show14six'] = array(
    '#prefix' => '<div align="left" id="part14_6_div">'.$output2,
    '#suffix' => '</div>',
       
  );











       $form['step14seveneightfield'] = array(
          '#title' => t(''),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 
$form['step14seveneightfield']['seven'] = array
              (
           '#prefix' => '<table class="table"><tr><td   >', 
           '#markup'=>'<b>    7    Details of violation in general visit (S/R) </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
$form['step14seveneightfield']['sevenvalue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
              '#default_value' =>$result_step14['details_of_violation_general_visit']
     
     
           ); 
$form['step14seveneightfield']['eighthead'] = array
              (
           '#prefix' => '<tr><td colspan="2"   >', 
           '#markup'=>'<b>    8  No. of prosecution </b>',

              '#suffix'=>'</td></tr>',
     
     
           ); 
        
          
           $form['step14seveneightfield']['eightone'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    a)  In connection with general visit </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
   $form['step14seveneightfield']['eightoneValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
          '#default_value' =>$result_step14['no_of_prosecution_general_visit'],
          '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           ); 


       $form['step14seveneightfield']['eighttwo'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    b)  In connection with complaint enquiry </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
   $form['step14seveneightfield']['eighttwoValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr>',
            '#default_value' =>$result_step14['no_of_prosecution_complaint'],
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           ); 


            $form['step14seveneightfield']['eightthree'] = array
              (
           '#prefix' => '<tr><td   >', 
           '#markup'=>'<b>    c)  In connection with accident enquiry </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
       $form['step14seveneightfield']['eightthreeValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
            '#default_value' =>$result_step14['no_of_prosecution_accident'],
            '#element_validate' => array('MONTHLY_MANDATORY_INTEGER_CHECKING_validate'),
     
     
           ); 

               $form['step14seveneightfield']['submit_button_1478A']         = array(
                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                '#type'         =>'submit',
                                '#value'        =>t(' Save  '),
                                
                                '#submit' => array('step14_part7and8_save'),
                                 
                                );


             $form['step14ninefield'] = array(
          '#title' => t('<font color="DarkGreen"><b>   9.  Details of prosecution against whom launched   </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          ); 

           

            $form['step14ninefield']['nineone'] = array
              (
           '#prefix' => '<table class="table"><tr><td   >', 
           '#markup'=>'<b>    a)  Violation (S/R) </b>',

              '#suffix'=>'</td>',
     
     
           ); 


              $form['step14ninefield']['ninetwo'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>    b)  Name of the Court </b>',

              '#suffix'=>'</td>',
     
     
           ); 
          
      
               $form['step14ninefield']['ninethree'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>      c)  Case No </b>',

              '#suffix'=>'</td>',
     
     
           ); 

               $form['step14ninefield']['ninefour'] = array
              (
           '#prefix' => '<td   >', 
           '#markup'=>'<b>         d)  Result / Remarks </b>',

              '#suffix'=>'</td></tr>',
     
     
           );

           $form['step14ninefield']['nineoneValue'] = array
              (
           '#prefix' => ' <tr><td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
             //'#default_value' =>$result_step14['details_of_prosecution_court_name']
     
     
           );  
          
       $form['step14ninefield']['ninetwoValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
             //'#default_value' =>$result_step14['details_of_prosecution_court_name']
     
     
           );

           
          
       $form['step14ninefield']['ninethreeValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td>',
             // '#default_value' =>$result_step14['details_of_prosecution_case_no']
     
     
           );

            
          
       $form['step14ninefield']['ninefourValue'] = array
              (
           '#prefix' => ' <td  >', 
           '#type' => 'textarea',
           
            '#rows' => 3,
            '#cols' => 3,

            '#suffix'=>'</td></tr></table>',
            //  '#default_value' =>$result_step14['details_of_prosecution_result']
     
     
           );
              $form['step14ninefield']['submit_button']          = array(
                                 
                                '#prefix' => '<div style="text-align:center;" >',
                                '#suffix'=>'</div>', 
                              
                              
                               // '#submit' => array('mr_step4_parta_save'),
                               '#type' => 'button',
                              '#event' => 'click',

                              '#default_value' => 'ADD   ',
                              '#ajax' => array(
                              'callback' => 'add_step14_part9',
                              'wrapper' => 'part14_9_div',
                              'method' => 'html',
                              'effect' => 'fade'
                               )

                                );

     $output1='';
      if(trim($filenumber)){
      $query_tab_14_9=db_query('select  *  from labour_factory_statcell_form_5_t14_9  where monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      if($query_tab_14_9->rowCount() > 0) 
              { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      <th > SL NO</th>
       <th > Violation (S/R)</th>
       <th > Name of the Court</th>
      
      <th >Case No</th>
       
     <th >Result / Remarks</th>

   
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_14_9 as $squan) {
      $i++;
          $prosecution_id = $squan->prosecution_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $details_of_prosecution_violation=$squan->details_of_prosecution_violation;

          $details_of_prosecution_court_name=$squan->details_of_prosecution_court_name;
          $details_of_prosecution_case_no=$squan->details_of_prosecution_case_no;
          $details_of_prosecution_result=$squan->details_of_prosecution_result;
       

              
              
              
      

          $bb=$base_root.$base_path.'admin/monthly-report-fourteen9del/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$prosecution_id);
      
    
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
                $output1.= "<td>".$details_of_prosecution_violation."</td>";
                $output1.= "<td>".$squan->details_of_prosecution_court_name."</td>";
                $output1.= "<td>".$squan->details_of_prosecution_case_no."</td>";
              

                 $output1.= "<td>".$squan->details_of_prosecution_result."</td>";
                
                
                $output1.= "<td >".$del_preper."</td>";
      
              
              $output1 .= "</tr>";
            }
              $output1 .= "</table>";
        
      

  
     }
  }
   $form['step14ninefield']['show14nine'] = array(
    '#prefix' => '<div align="left" id="part14_9_div">'.$output1,
    '#suffix' => '</div>',
       
  );



 

           return $form;
         }



     function add_step14_part9($form , $form_state) { 
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $val=$form_state['values'];



  $monthlyformid=trim($val['monthlyformid']);
    
  $nineoneValue=trim($val['nineoneValue']); if(!$nineoneValue) $nineoneValue= NULL;
  $ninetwoValue=trim($val['ninetwoValue']); if(!$ninetwoValue) $ninetwoValue= NULL;
  $ninethreeValue=trim($val['ninethreeValue']); if(!$ninethreeValue) $ninethreeValue= NULL;
  $ninefourValue=trim($val['ninefourValue']); if(!$ninefourValue) $ninefourValue= NULL;  

  

 
        

     // return  $fourvalue;
  
   
      


     $txn = db_transaction();

        try {
     
   
   
            $maxresult=db_query('select  max(prosecution_id) maxsl from labour_factory_statcell_form_5_t14_9');  
            $result=$maxresult->fetchAssoc();
            $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
             $autoGENNO=$querystring;


      $fieldsE = array('prosecution_id' =>$autoGENNO, 'monthly_form_id' => $monthlyformid, 'details_of_prosecution_violation' => $nineoneValue, 'details_of_prosecution_court_name' => $ninetwoValue,  'details_of_prosecution_case_no' => $ninethreeValue ,  'details_of_prosecution_result' => $ninefourValue );
      
        db_insert('labour_factory_statcell_form_5_t14_9')->fields($fieldsE)->execute(); 
   
   
  $query_tab_14_9=db_query('select  *  from labour_factory_statcell_form_5_t14_9  where  monthly_form_id = :anid', array(':anid' => trim($monthlyformid) ));
      //if($query_tab_1_c->rowCount() > 0) 
             // { 
     $output1 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
   
      <tr > 
      <th > SL NO</th>
       <th > Violation (S/R)</th>
       <th > Name of the Court</th>
      <th >Case No</th>
       
     <th >Result / Remarks</th>

   
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_14_9 as $squan) {
      $i++;
          $prosecution_id = $squan->prosecution_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $details_of_prosecution_violation=$squan->details_of_prosecution_violation;

          $details_of_prosecution_court_name=$squan->details_of_prosecution_court_name;
          $details_of_prosecution_case_no=$squan->details_of_prosecution_case_no;
          $details_of_prosecution_result=$squan->details_of_prosecution_result;
       

              
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fourteen9del/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$prosecution_id);
      
    
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
                $output1.= "<td>".$details_of_prosecution_violation."</td>";
                $output1.= "<td>".$squan->details_of_prosecution_court_name."</td>";
                $output1.= "<td>".$squan->details_of_prosecution_case_no."</td>";
              

                 $output1.= "<td>".$squan->details_of_prosecution_result."</td>";
                
                
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

  function step14_9_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t14_9')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('prosecution_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step14/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }




   function step14_6_del(  $filenumber = NULL , $rowid = NULL){
    
   global $base_root, $base_path;
    

     $filenumber=  encryption_decryption_fun('decrypt',trim($filenumber));
     
      $rowid=  encryption_decryption_fun('decrypt',trim($rowid));
     // print $filenumber.'ddd'. $rowid;
     // exit;
     
  $txn = db_transaction();
    try {
      
    db_delete('labour_factory_statcell_form_5_t14_6')
    ->condition('monthly_form_id',trim($filenumber))
    ->condition('accident_id',trim($rowid))
    ->execute();
  
  
  $message = '   delete is successfull ';
  
}
  catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
  $message = '    row is not  delete ';
     }  
  
     //$aa=$base_root.$base_path.'equalremuins/equalinfringements/'.encryption_decryption_fun('encrypt', trim($filenumber));

      $aa=$base_root.$base_path.'admin/monthly-report/step14/'.encryption_decryption_fun('encrypt',$filenumber);
      drupal_set_message(t($message));
     
      drupal_goto($aa);
      
  }


      function month_report_step14_parta_save($form , $form_state) { 


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
 /* 


  $eightthreeValue=trim($val['eightthreeValue']); if(!$eightthreeValue) $eightthreeValue= NULL;
  $nineoneValue=trim($val['nineoneValue']); if(!$nineoneValue) $nineoneValue= NULL;
  $ninetwoValue=trim($val['ninetwoValue']); if(!$ninetwoValue) $ninetwoValue= NULL;
  $ninethreeValue=trim($val['ninethreeValue']); if(!$ninethreeValue) $ninethreeValue= NULL;
  $ninefourValue=trim($val['ninefourValue']); if(!$ninefourValue) $ninefourValue= NULL; */
  $tenValue=trim($val['tenValue']); if(!$tenValue) $tenValue= NULL;
  

  $txn = db_transaction();
    try {



            $query_update_yes=db_query('select  * from labour_factory_statcell_form_5_t14_6_t6_7_t8 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
       if($query_update_yes->rowCount() > 0) 
          {
         $query_update_A = db_update('labour_factory_statcell_form_5_t14_6_t6_7_t8');
        $query_update_A->fields(array(
     'no_of_units_visit'=> $onevalue , 'no_of_visit_paid_general' =>$twooneValue,  'no_of_visit_paid_complaint' =>$twotwoValue,'no_of_visit_paid_accident' =>$twothreeValue, 'no_of_complaints_received' => $threeValue, 'details_of_complaint' => $fourValue,  'no_of_accidents_reported' => $fiveValue, 'other_information' => $tenValue


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



          

       $fieldsA = array('bocw_id' => $rowid ,'monthly_form_id' => $monthly_form_id,'form_type' => 'GENERAL', 'no_of_units_visit'=> $onevalue , 'no_of_visit_paid_general' =>$twooneValue,  'no_of_visit_paid_complaint' =>$twotwoValue,'no_of_visit_paid_accident' =>$twothreeValue, 'no_of_complaints_received' => $threeValue, 'details_of_complaint' => $fourValue,  'no_of_accidents_reported' => $fiveValue,   'other_information' => $tenValue


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


   

    function step14_part7and8_save($form , $form_state) { 


         global $base_root, $base_path,$full_base;




   $val=$form_state['values'];

 
  $monthly_form_id=trim($val['monthlyformid']); 

 // print $monthly_form_id;  
 // exit; 

  


  
  $sevenvalue=trim($val['sevenvalue']); if(!$sevenvalue) $sevenvalue= NULL;
  $eightoneValue=trim($val['eightoneValue']); if(!$eightoneValue) $eightoneValue= NULL;
  $eighttwoValue=trim($val['eighttwoValue']); if(!$eighttwoValue) $eighttwoValue= NULL;


  $eightthreeValue=trim($val['eightthreeValue']); if(!$eightthreeValue) $eightthreeValue= NULL;
  
  

  $txn = db_transaction();
    try {



            $query_update_yes=db_query('select  * from labour_factory_statcell_form_5_t14_6_t6_7_t8 where  monthly_form_id = :filenumber', array(':filenumber' => $monthly_form_id));


             
       if($query_update_yes->rowCount() > 0) 
          {
         $query_update_A = db_update('labour_factory_statcell_form_5_t14_6_t6_7_t8');
        $query_update_A->fields(array(
       'details_of_violation_general_visit' => $sevenvalue,  'no_of_prosecution_general_visit' => $eightoneValue,'no_of_prosecution_complaint' => $eighttwoValue

      , 'no_of_prosecution_accident' => $eightthreeValue


   ));
                    
                    
                    
       $query_update_A->condition('monthly_form_id',$monthly_form_id);
       $query_update_A->execute(); 


           $full_base=$base_root.$base_path.'admin/monthly-report/step14/'.encryption_decryption_fun('encrypt',$monthly_form_id);

             $message = 'DATA  SAVED SUCCESSFULLY  . ';
                      
       
               drupal_set_message(t($message));
             
               drupal_goto($full_base);

          }
          


   

          

              

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



   
 function add_step14_part6($form , $form_state) { 
       global $base_root, $base_path;
       $val=$form_state['values'];


    
 
      $val=$form_state['values'];



  $monthlyformid=trim($val['monthlyformid']);
    
  
  
  

  $sixValue=trim($val['sixValue']); if(!$sixValue) $sixValue= NULL;
  $sixtwoValue=trim($val['sixtwoValue']); if(!$sixtwoValue) $sixtwoValue= NULL;
  $sixthreeValue=trim($val['sixthreeValue']); if(!$sixthreeValue) $sixthreeValue= NULL;


  $sixfourValue=trim($val['sixfourValue']); 


  if(!$sixfourValue)  
    $sixfourValue= NULL; 
    else
  $sixfourValue= date('Y-m-d', strtotime($sixfourValue));    

  $sixfiveValue=trim($val['sixfiveValue']); if(!$sixfiveValue) $sixfiveValue= NULL;
  $sixsixValue=trim($val['sixsixValue']); if(!$sixsixValue) $sixsixValue= NULL;
  //$sixsevenValue=trim($val['sixsevenValue']); if(!$sixsevenValue) $sixsevenValue= NULL;
  $sixeightValue=trim($val['sixeightValue']); if(!$sixeightValue) $sixeightValue= NULL;


  $sixnineValue=trim($val['sixnineValue']); if(!$sixnineValue) $sixnineValue= NULL;
  $sixtenValue=trim($val['sixtenValue']); if(!$sixtenValue) $sixtenValue= NULL;
 

     // return  $fourvalue;
  
   if(trim($sixtwoValue) && !preg_match('/^[0-9]+$/',trim($sixtwoValue))) {
    drupal_get_messages(error);
    return "<font color='#FF3333'><b>   age should be   number <b>    </font>";
    exit;  
   } 
      


     $txn = db_transaction();

        try {
     
   
   
            $maxresult=db_query('select  max(accident_id) maxsl from labour_factory_statcell_form_5_t14_6');  
            $result=$maxresult->fetchAssoc();
            $max_sl_number = trim($result['maxsl']); 
            if($max_sl_number==0){$querystring=1; }else{ $querystring=$max_sl_number+1; }
             $autoGENNO=$querystring;


      $fieldsE = array('accident_id' =>$autoGENNO, 'monthly_form_id' => $monthlyformid,'accident_details_name_of_deceased' => $sixValue, 'accident_details_age' => $sixtwoValue, 'accident_details_sex' => $sixthreeValue, 'accident_details_date_of_accident' => $sixfourValue, 'accident_details_nature_of_accident' => $sixfiveValue, 'accident_details_description' => $sixsixValue, 'accident_details_place' => $sixeightValue, 'accident_details_name_of_employer' => $sixnineValue
      , 'accident_details_address_of_site' => $sixtenValue);
      
        db_insert('labour_factory_statcell_form_5_t14_6')->fields($fieldsE)->execute(); 
   
   
 
      //if($query_tab_1_c->rowCount() > 0) 
             // { 
      $query_tab_14_6=db_query('select  *  from labour_factory_statcell_form_5_t14_6  where monthly_form_id = :anid', array(':anid' => trim($monthlyformid) ));
     
     $output2 = "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      <th > SL NO</th>
       <th > Name of I.P/deceased (S/R)</th>
       <th > Age</th>
      
      <th >Sex</th>
       
     <th >Dt. & time of accident</th>

     <th >Nature of accident (serious/Fatal)</th>

   
     
     <th >DELETE</th>
    </tr>";  
        $i=0;
    foreach($query_tab_14_6 as $squan) {
      $i++;
          $accident_id = $squan->accident_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $accident_details_name_of_deceased=$squan->accident_details_name_of_deceased;

          $accident_details_age=$squan->accident_details_age;
          $accident_details_sex=$squan->accident_details_sex;
          $accident_details_date_of_accident=$squan->accident_details_date_of_accident;

          $accident_details_nature_of_accident=$squan->accident_details_nature_of_accident;
          $accident_details_description=$squan->accident_details_description;
          $accident_details_place=$squan->accident_details_place;
          $accident_details_name_of_employer=$squan->accident_details_name_of_employer;
          $accident_details_address_of_site=$squan->accident_details_address_of_site;
       

              
              
              
      

         $bb=$base_root.$base_path.'admin/monthly-report-fourteen6del/'.encryption_decryption_fun('encrypt',$monthly_form_id).'/'.encryption_decryption_fun('encrypt',$accident_id);
      
    
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
                $output2.= "<td>".$accident_details_name_of_deceased."</td>";
                $output2.= "<td>".$squan->accident_details_age."</td>";
                $output2.= "<td>".$squan->accident_details_sex."</td>";
              

                 $output2.= "<td>".date('d-m-Y', strtotime($squan->accident_details_date_of_accident))."</td>";

                  $output2.= "<td>".$squan->accident_details_nature_of_accident."</td>";
                
                
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


     

           ?>