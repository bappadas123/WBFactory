<?php
function month_report_step17( $form, &$form_state, $filenumber= NULL   ){
	
	
	 global $base_root, $base_path , $user;

    $filenumber= encryption_decryption_fun('decrypt', trim($filenumber));

     //$options_classification = array(0 => " Select  ") + an_classification_option();

    $form['step17field'] = array(
          '#title' => t('<font color="DarkGreen"><b>  View & Submit  </b></font>'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );

 $form['step17field']['monthlyformid'] = 
      array('#type' => 'hidden',  
      '#value' => $filenumber,
     
     );


      $content = '<style type="text/css">
          table, td, th {
              font-size:12px;
              font-family:Times New Roman;
              height:15px;
              color:#000;
              margin-top:10px;
              background:#fff;
          }
          th {
            background-color: #008BD1;
            color: white;
          }
          td:hover {
            background-color:#d4e3e5;
          }
          h1 {
            font-size:11px;
            font-weight:normal;
          }
          h2,h3,h4 {
            font-size:12px;
          }
          .data{ text-transform: uppercase;font-weight:bold;}
          
      </style>';


        $mr_istquery = db_select('labour_factory_statcell_form_5', 'a');
       

        $mr_istquery->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id','report_month','report_year'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
    $result_mrist=$mr_istquery_result->fetchAssoc();
    $area=$result_mrist['area'];
    $report_year=$result_mrist['report_year'];
     $report_month=$result_mrist['report_month'];
    $inspector_id=$result_mrist['inspector_id'];

    //print 'sss'.$inspector_id;
     // exit;
    
    $query_uname=db_query('select fname from fa_employee_details where uid = :fuid  ', array(':fuid' => trim($inspector_id)));
    $inspector_name='';
    if($query_uname->rowCount() > 0)
      //print 'sss'.$inspector_id;
      //exit;
     $inspector_name=get_name($inspector_id);
    else
    {
    
    $query_newinsid=db_query('select fa_uid  from tm_users where old_uid = :ouid  ', array(':ouid' => trim($inspector_id)));

    $result_newinsId=$query_newinsid->fetchAssoc();
    $inspector_id = $result_newinsId['fa_uid']; 

    $inspector_name=get_name($inspector_id);
    //print 'sss'.$inspector_name;

    }

$content = '<table width="100%" >       
          <tr><td colspan="3"></td></tr>        
           <tr><td colspan="4" align="center" style="font-size:20px;text-transform:uppercase;"><h4> Report for the month of - '.date("F", mktime(0, 0, 0, $report_month, 10)) .', '.$report_year.'  </h2></td></tr>
            <tr><td colspan="2" align="center" style="font-size:20px;text-transform:uppercase; text-align: left"><h5><b>Name of the Inspector- '.$inspector_name.'  </b></h2></td>
                     <td colspan="2" align="center" style="font-size:20px;text-transform:uppercase;"><h5><b>Area- '.$area.' </b></h2></td></tr>
                        
          <tr><td colspan="3"></td></tr>
          <tr><td colspan="3"></td></tr></table>';





          $content .= ' 
    <div><b>1.Inspection (A).. </b></div>
  <div align="center"><b> No. of units visited</b> </div>

  <table width="100%" border="1"   >
                                                
                                                    <tr>
                                                        <th rowspan="4" align="center" valign="middle" >Group</th>
                                                        <th colspan="8" align="center" valign="middle">No. of units visited</th>
                                                      
                                                    </tr>


                                                    <tr>
                                                        <th colspan="3" align="center" valign="middle" >Registered factories u/s</th>
                                                        <th colspan="3" align="center" valign="middle" >Unregistered amenable factories u/s</th>
                                                        <th rowspan="3" align="center" valign="middle" >Not amenable factories</th>
                                                        <th rowspan="3" align="center" valign="middle" >Total</th>
                                                      
                                                    </tr>

                                                    <tr>
                                                        <th colspan="2" align="center" valign="middle" >2(m)</th>
                                                        <th rowspan="2" align="center" valign="middle">85</th>
                                                        <th colspan="2" align="center" valign="middle" >2(m)</th>
                                                        <th rowspan="2" align="center" valign="middle">85</th>
                                                      
                                                    </tr>
                                                    <tr>
                                                        <th  align="center" valign="middle" >(i)</th>
                                                        <th  align="center" valign="middle">(ii)</th>
                                                        <th  align="center" valign="middle" >(i)</th>
                                                        <th  align="center" valign="middle">(ii)</th>
                                                      
                                                    </tr>';

        $step1_select_query = db_select('labour_factory_statcell_form_5_6_7_t1', 'a');
       
        $step1_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step1_select_query->fields('a',array('g_nouv_regfac_2m_i','g_nouv_regfac_2m_ii','g_nouv_regfac_85','g_nouv_unregfac_2m_i','g_nouv_unregfac_2m_ii','g_nouv_unregfac_85','g_nouv_non_amendable','g_nouv_total', 'g_novp_regfac_2m_i','g_novp_regfac_2m_ii','g_novp_regfac_85','g_novp_unregfac_2m_i','g_novp_unregfac_2m_ii','g_novp_unregfac_85','g_novp_non_amendable','g_novp_total','h_nouv_regfac_2m_i','h_nouv_regfac_2m_ii','h_nouv_regfac_85','h_nouv_unregfac_2m_i','h_nouv_unregfac_2m_ii','h_nouv_unregfac_85','h_nouv_non_amendable','h_nouv_total',
        'h_novp_regfac_2m_i','h_novp_regfac_2m_ii','h_novp_regfac_85','h_novp_unregfac_2m_i','h_novp_unregfac_2m_ii','h_novp_unregfac_85','h_novp_non_amendable','h_novp_total',
        'mah_nouv_regfac_2m_i','mah_nouv_regfac_2m_ii','mah_nouv_regfac_85','mah_nouv_unregfac_2m_i','mah_nouv_unregfac_2m_ii','mah_nouv_unregfac_85','mah_nouv_non_amendable','mah_nouv_total','mah_novp_regfac_2m_i','mah_novp_regfac_2m_ii','mah_novp_regfac_85','mah_novp_unregfac_2m_i','mah_novp_unregfac_2m_ii','mah_novp_unregfac_85','mah_novp_non_amendable','mah_novp_total'));
        $step1_select_query_result = $step1_select_query->execute(); 
    
    $result_step1_A=$step1_select_query_result->fetchAssoc();
    $g_nouv_regfac_2m_i=$result_step1_A['g_nouv_regfac_2m_i'];


    

                                                    $content .= '  <tr>
                                                        <td  align="center" valign="middle" >G</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_nouv_regfac_2m_i'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_nouv_regfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_nouv_regfac_85'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_nouv_unregfac_2m_i'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_nouv_unregfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_nouv_unregfac_85'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_nouv_non_amendable'].' </td>  
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_nouv_total'].' </td>
                                                        
                                                      
                                                    </tr>
                                                    <tr>
                                                        <td  align="center" valign="middle" >H</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_regfac_2m_i'] .'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_regfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_regfac_85'] .'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_unregfac_2m_i'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_unregfac_2m_ii'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_unregfac_85'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_non_amendable'] .'</td>  
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_nouv_total'].'</td>
                                                        
                                                      
                                                    </tr>
                                                    <tr>
                                                        <td  align="center" valign="middle" >MAH</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_regfac_2m_i'] .'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_regfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_regfac_85'] .'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_unregfac_2m_i'] .'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_unregfac_2m_ii'] .'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_unregfac_85'] .'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_non_amendable'] .'</td>   
                                                        <td  align="center" valign="middle">'.$result_step1_A['mah_nouv_total'] .'</td>
                                                        
                                                      
                                                    </tr>
                                                   
                                                    </table>
                                                    <div align="left"><b> Inspection (B) </b></div>
                                                    <div align="center"><b> No. of visits paid to </b></div>
                                                    <table width="100%" border="1"   >
                                                
                                                    <tr>
                                                        <th rowspan="4" align="center" valign="middle" >Group</th>
                                                        <th colspan="8" align="center" valign="middle">No. of visits paid to</th>
                                                      
                                                    </tr>


                                                    <tr>
                                                        <th colspan="3" align="center" valign="middle" >Registered factories u/s</th>
                                                        <th colspan="3" align="center" valign="middle" >Unregistered amenable factories u/s</th>
                                                        <th rowspan="3" align="center" valign="middle" >Not amenable factories</th>
                                                        <th rowspan="3" align="center" valign="middle" >Total</th>
                                                      
                                                    </tr>

                                                    <tr>
                                                        <th colspan="2" align="center" valign="middle" >2(m)</th>
                                                        <th rowspan="2" align="center" valign="middle">85</th>
                                                        <th colspan="2" align="center" valign="middle" >2(m)</th>
                                                        <th rowspan="2" align="center" valign="middle">85</th>
                                                      
                                                    </tr>
                                                    <tr>
                                                        <th  align="center" valign="middle" >(i)</th>
                                                        <th  align="center" valign="middle">(ii)</th>
                                                        <th  align="center" valign="middle" >(i)</th>
                                                        <th  align="center" valign="middle">(ii)</th>
                                                      
                                                    </tr>

                                                     <tr>
                                                        <td  align="center" valign="middle" >G</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_novp_regfac_2m_i'].'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_novp_regfac_2m_ii'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_novp_regfac_85'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_novp_unregfac_2m_i'].'</td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_novp_unregfac_2m_ii'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_novp_unregfac_85'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['g_novp_non_amendable'].'</td>   
                                                        <td  align="center" valign="middle">'.$result_step1_A['g_novp_total'].' </td>
                                                        
                                                      
                                                    </tr>
                                                    <tr>
                                                        <td  align="center" valign="middle" >H</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_regfac_2m_i'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_regfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_regfac_85'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_unregfac_2m_i'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_unregfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_unregfac_85'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_non_amendable'].' </td>  
                                                        <td  align="center" valign="middle"> '.$result_step1_A['h_novp_total'].' </td>
                                                        
                                                      
                                                    </tr>
                                                    <tr>
                                                        <td  align="center" valign="middle" >MAH</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_regfac_2m_i'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_regfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_regfac_85'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_unregfac_2m_i'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_unregfac_2m_ii'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_unregfac_85'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_non_amendable'].' </td>  
                                                        <td  align="center" valign="middle"> '.$result_step1_A['mah_novp_total'].'</td>
                                                        
                                                      
                                                    </tr>
                                                   
                                                    </table>';

          $step2_select_query = db_select('labour_factory_statcell_form_5_6_7_t2', 'a');
       
        $step2_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step2_select_query->fields('a',array('visit_pwa','visit_mba','visit_msihcr','visit_car','visit_clpra','visit_rest_interval','visit_bef_after_legal_hours','visit_sunday_holiday','visit_approval_of_plan','visit_reg_licence','visit_collection_statistics','visit_enq_complaints','visit_court_attendance','visit_attn_seminar_meeting','visit_to_closed_factory','visit_others','visit_total'));
        $step2_select_query_result = $step2_select_query->execute(); 
    
         $result_step2=$step2_select_query_result->fetchAssoc();


                      $content .= '<div><b> 2. No. of Special Visit </b></div>

                     <table width="100%" border="1"   >
                                                
                                                    <tr>
                                                        <th colspan="5" align="center" valign="middle" >Exclusively under</th>
                                                        <th rowspan="2" align="center" valign="middle">During <br>rest <br>Interval</th>
                                                        <th rowspan="2" align="center" valign="middle">Before or <br> after <br>legal hours</th>
                                                        <th rowspan="2" align="center" valign="middle">On <br> Sundays and <br>Holidays</th>
                                                        <th rowspan="2" align="center" valign="middle">For approval <br> of plans</th>
                                                        <th rowspan="2" align="center" valign="middle">For <br> registration <br> and licence</th>
                                                        <th rowspan="2" align="center" valign="middle">For <br>collections of <br> statistic</th>
                                                        <th rowspan="2" align="center" valign="middle">For  <br> enquiry <br> into complaints</th>
                                                        <th rowspan="2" align="center" valign="middle">For court <br>attendance</th>
                                                        <th rowspan="2" align="center" valign="middle">For <br>attending <br> safety <br> seminars, <br> meetings etc</th>
                                                        <th rowspan="2" align="center" valign="middle">To closed <br>factories</th>
                                                        <th rowspan="2" align="center" valign="middle">Others</th>
                                                        <th rowspan="2" align="center" valign="middle">Total</th>
                                                      
                                                      
                                                    </tr>


                                                 <tr>
                                                        <th  align="center" valign="middle" >PWA</th>
                                                        <th  align="center" valign="middle">MBA</th>
                                                        <th  align="center" valign="middle">MSIHCR</th>
                                                        <th  align="center" valign="middle">CAR</th>
                                                        <th  align="center" valign="middle">CL(P&R)A</th>
                              
                                                        
                                                      
                                                      
                                                    </tr>

                                                    <tr>
                                                       
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_pwa'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_mba'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_msihcr'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_car'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_clpra'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_rest_interval'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_bef_after_legal_hours'].' </td>  
                                                        <td  align="center" valign="middle"> '.$result_step2['visit_sunday_holiday'].'</td>

                                                          <td  align="center" valign="middle"> '.$result_step2['visit_approval_of_plan'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step2['visit_reg_licence'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step2['visit_collection_statistics'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step2['visit_enq_complaints'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step2['visit_court_attendance'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step2['visit_attn_seminar_meeting'].'</td>
                                                         <td  align="center" valign="middle"> '.$result_step2['visit_to_closed_factory'].'</td>
                                                         <td  align="center" valign="middle"> '.$result_step2['visit_others'].'</td>
                                                         <td  align="center" valign="middle"> '.$result_step2['visit_total'].'</td>
                                                    </tr>


                      </table>';

             // chemical inspector

               if(array_key_exists(14, $user->roles)){

                $content .= " <div><b> 3. Relevant particulars of inspection </b></div> ";

 $query_step6=db_query('select  *  from labour_factory_statcell_form_5_t6_6_t3 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr> <th rowspan='2' >Name of the Factory</th>
      
       <th rowspan='2' > Address of the Factory</th>
       <th colspan='2' > Raw Materials Used</th>
       <th colspan='2' > Intermediaries</th>
       <th colspan='2' > Products Manufactured</th>

      <th rowspan='2' >Possible Hazards</th>
      <th rowspan='2' >Action Taken / Remarks</th>
    </tr>
    <tr>
      <th >Name</th>
       
     <th >Max. Qty. Stored</th>

    

     <th >Name</th>
     <th >Max. Qty. Stored</th>
       
      <th >Name</th>
      <th >Max. Qty. Stored</th>

     
       
     
   
    </tr>";  
        $i=0;
    foreach($query_step6 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->chem_fac_id; 
           
              
              
      

       
             
               $content .= "<tr >";
        
        
        
                $content.= "<td>".$squan->chem_fac_name_of_factory."</td>";
                $content.= "<td>".$squan->chem_fac_address_of_factory."</td>";
                $content.= "<td>".$squan->chem_fac_raw_mat_name."</td>";
                $content.= "<td>".$squan->chem_fac_raw_mat_quantity."</td>";
                
             
                $content.= "<td>".$squan->chem_fac_intermediaries_name."</td>";
                $content.= "<td>".$squan->chem_fac_intermediaries_quantity."</td>";

                $content.= "<td>".$squan->chem_fac_products_name."</td>";
                $content.= "<td>".$squan->chem_fac_products_quantity."</td>";

                $content.= "<td>".$squan->chem_fac_possible_hazards."</td>";
                $content.= "<td>".$squan->chem_fac_action_remarks."</td>";
        
       
      
      
              
               $content .= "</tr>";
            }
              $content .= "</table>";


     $step16_select_query = db_select('labour_factory_statcell_form_5_compliance_for_chemical', 'a');
       
      $step16_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step16_select_query->fields('a',array( 'on_site_plan_submitted'  ,'safety_audit_conducted' ,'on_site_emergency_mock_drills','no_of_mah_factories_identified' ));
        $step16_select_query_result = $step16_select_query->execute(); 
    
        $result_step16=$step16_select_query_result->fetchAssoc();

     $content .= "
               <div><b> 4. Information regarding compliance in the factories inspected for </b></div>

          <table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >On site plan submitted/resubmitted for examination</th>
      
       <th > Safety audit conducted</th>
      
       
        <th >On-site emergency mock drills conducted</th>

    

    
    </tr>
     <tr >";
      
      
                $content.= "<td>".$result_step16['on_site_plan_submitted'] ."</td>";
                $content.= "<td>".$result_step16['safety_audit_conducted']."</td>";
                $content.= "<td>".$result_step16['on_site_emergency_mock_drills'] ."</td></tr>";

                $content.= "<tr><td colspan='2'><b>No of MAH Factories identified </b> </td> <td>".$result_step16['no_of_mah_factories_identified'] ."</td></tr></table> <br><br>";


$query_step12=db_query('select  *  from labour_factory_statcell_form_5_t12_6_t5_7_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));

      $content .= "
               <div><b> 5. Details of Seminars/Training Courses etc. </b></div>

          <table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Type of program</th>

    

     <th >Date of program</th>
      <th >No. of participants</th>
      <th >Status of participants</th>
    
    </tr>";  
      
    foreach($query_step12 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->seminar_id; 
         
        
            
              $content .= "<tr >";
      
      
                $content.= "<td>".$squan->seminar_name_of_factory."</td>";
                $content.= "<td>".$squan->seminar_address_of_factory."</td>";
                $content.= "<td>".$squan->seminar_type_of_program."</td>";
                $content.= "<td>".$squan->seminar_date_of_program."</td>";
                $content.= "<td>".$squan->seminar_no_of_participants."</td>";
                $content.= "<td>".$squan->seminar_status_of_participants."</td>";
             
           
              
         $content .= "</tr>";
            }
        $content .= "</table><br><br>";


               }

              elseif(array_key_exists(15, $user->roles)){

               // medical inspector

           
           $step15_select_query = db_select('labour_factory_statcell_form_5_medical_examination', 'a');
       
          $step15_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step15_select_query->fields('a',array( 'adolescent_no_certified'  ,'adolescent_no_recertified' ,'adolescent_no_rejected','children_no_certified' ,'children_no_recertified'  ,'children_no_rejected'  ,'nature_of_industry'  ,'no_of_workers_examined' ,'comments_on_fitness'));
        $step15_select_query_result = $step15_select_query->execute(); 
    
         $result_step15=$step15_select_query_result->fetchAssoc();

                  $content .= "<div><b> 3. Details of Medical Examination. </b></div>

          <table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th rowspan='2' >Young Person</th>
      
       <th rowspan='2' > No certified</th>
      
       
     <th rowspan='2' >No. recertified</th>

    

     <th rowspan='2' >No. rejected</th>
      <th colspan='3' >No. of workers examined under provision of West Bengal Factories rules , 1958</th>
     
    
    </tr>

   <tr > <th >Nature of Industry</th>
      
       <th > No of workers examined</th>
      
       
     <th >Comments on-fitness</th>

    

    
     
    
    </tr>
   <tr>
        <td>Adolescent </td> 
        <td>".$result_step15['adolescent_no_certified'] ."</td> 
        <td>".$result_step15['adolescent_no_recertified']." </td> 
        <td>".$result_step15['adolescent_no_rejected'] ." </td>

        <td rowspan='2'>".$result_step15['nature_of_industry']." </td> 
        <td rowspan='2'>".$result_step15['no_of_workers_examined'] ." </td> 
        <td rowspan='2' >".$result_step15['comments_on_fitness'] ." </td> 
        </tr>


        <tr>
        <td>Children </td> 
        <td>".$result_step15['children_no_certified']  ." </td> 
        <td>".$result_step15['children_no_recertified'] ." </td> 
        <td>".$result_step15['children_no_rejected'] ."</td>
        </tr>




    </table>

    "; 

     $content .= "<div><b> 4. Notifiable diseases / Cases of Poisoning </b></div>";
$query_step5=db_query('select  *  from labour_factory_statcell_form_5_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
     
     $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      <th >Nature of Mfg. process</th>
       
     <th >Name of persons involved</th>

     <th >Occupation</th>
       
     <th >Name of the disease / poison</th>
      <th >Action Taken/ Remarks</th>
       
     
    
    </tr>";  
        $i=0;
    foreach($query_step5 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->notifiable_desease_id; 
           
              
              
      

        
        //$output1.= "<td>".$i."</td>"; 
               $content.= "<tr>";
                $content.= "<td>".$squan->nd_name_of_factory."</td>";
                $content.= "<td>".$squan->nd_address_of_factory."</td>";
                $content.= "<td>".$squan->nd_nature_mfg_process."</td>";
                $content.= "<td>".$squan->nd_persons_involved."</td>";
                
             
                $content.= "<td>".$squan->nd_occupation."</td>";
                $content.= "<td>".$squan->nd_name_of_disease."</td>";
                $content.= "<td >".$squan->nd_action_remarks."</td>";
        
       
     
      
              
         $content .= "</tr>";
            }
        $content .= "</table>";


    $query_step12=db_query('select  *  from labour_factory_statcell_form_5_t12_6_t5_7_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
         $content .= "
               <div><b> 5. Details of Seminars/Training Courses etc. </b></div>

          <table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Type of program</th>

    

     <th >Date of program</th>
      <th >No. of participants</th>
      <th >Status of participants</th>
    
    </tr>";  
      
    foreach($query_step12 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->seminar_id; 
         
        
            
              $content .= "<tr >";
      
      
                $content.= "<td>".$squan->seminar_name_of_factory."</td>";
                $content.= "<td>".$squan->seminar_address_of_factory."</td>";
                $content.= "<td>".$squan->seminar_type_of_program."</td>";
                $content.= "<td>".date('d-m-Y', strtotime($squan->seminar_date_of_program))."</td>";
                $content.= "<td>".$squan->seminar_no_of_participants."</td>";
                $content.= "<td>".$squan->seminar_status_of_participants."</td>";
             
           
              
         $content .= "</tr>";
            }
        $content .= "</table>



           <div><b> 6. Prosecution Proceedings instituted </b></div>";


             

        $query_step9=db_query('select  *  from labour_factory_statcell_form_5_t9_7_t6 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));        
      $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of <br> the Factory</th>
      
       <th > Address of <br> the Factory</th>
      <th >Registered <br>/Unregistered</th>
       
     <th >Person Prosecuted <br>(Occupier, Manager etc)</th>

    

     <th >Case No.</th>
      <th >Name of <br>the act.</th>
      <th >Violation.</th>
      <th >Penal Provision</th>
      <th >Name of the Court</th>
      <th >Remarks / Result</th>
    
       
     
    
    </tr>";  
     
    foreach($query_step9 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->pros_instituted_id; 
         
           
              $content .= "<tr >";
       
      
                $content.= "<td>".$squan->pros_instituted_name_of_factory."</td>";
                $content.= "<td>".$squan->pros_instituted_address_of_factory."</td>";
                $content.= "<td>".$squan->pros_instituted_reg_unreg."</td>";
                $content.= "<td>".$squan->pros_instituted_person_prosecuted."</td>";
                $content.= "<td>".$squan->pros_instituted_case_no."</td>";
                $content.= "<td>".$squan->pros_instituted_name_of_act."</td>";
                $content.= "<td>".$squan->pros_instituted_violation."</td>";
                $content.= "<td>".$squan->pros_instituted_penal_provision."</td>";
                $content.= "<td>".$squan->pros_instituted_name_of_court."</td>";
                $content.= "<td>".$squan->pros_instituted_remarks_result."</td>";
              
               $content .= "</tr>";
            }
                
        
       
            
      
              
         
              $content .= "</table>";




                $content .= "<div><b> 7.  Particulars of the cases disposed off </b></div>";


 $query_step10=db_query('select  *  from labour_factory_statcell_form_5_t10_7_t7 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
     
     $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of <br>the Factory</th>
      
       <th > Address of <br> the Factory</th>
      
       
     <th >Person Prosecuted <br> (Occupier, Manager etc)</th>

    

     <th >Case No.</th>
      <th >Name of <br> the act.</th>
      <th >Violation.</th>
      <th >Result/ <br> Amount of the fine</th>
      <th >Date of <br> disposal</th>
      <th >Name of <br> the Court</th>
      <th >Remarks / <br> Result</th>
    
       
     
    
    </tr>";  
       
    foreach($query_step10 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->case_disposed_id; 
         
           
              
              
      

        
        
        
          
                 $content .= "<tr>";
        
                $content.= "<td>".$squan->case_disposed_name_of_factory."</td>";
                $content.= "<td>".$squan->case_disposed_address_of_factory."</td>";
                $content.= "<td>".$squan->case_disposed_person_prosecuted."</td>";
                $content.= "<td>".$squan->case_disposed_case_no."</td>";
                $content.= "<td>".$squan->case_disposed_name_of_act."</td>";
                $content.= "<td>".$squan->case_disposed_violation."</td>";
                $content.= "<td>".$squan->case_disposed_result_fine."</td>";
                $content.= "<td>".date('d-m-Y', strtotime($squan->case_disposed_date_of_disposal))."</td>";
                $content.= "<td>".$squan->case_disposed_name_of_court."</td>";
                $content.= "<td>".$squan->case_disposed_remarks_result."</td>";
                $content .= "</tr>";
               
           
        
            }
              $content .= "</table> ";
             







               }

               elseif(array_key_exists(9, $user->roles)){




        $step3_select_query = db_select('labour_factory_statcell_form_5_6_7_t2', 'a');
       
        $step3_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step3_select_query->fields('a',array('visit_pwa','visit_mba','visit_msihcr','visit_car','visit_clpra','visit_rest_interval','visit_bef_after_legal_hours','visit_sunday_holiday','visit_approval_of_plan','visit_reg_licence','visit_collection_statistics','visit_enq_complaints','visit_court_attendance','visit_attn_seminar_meeting','visit_to_closed_factory','visit_others','visit_total'));
        $step3_select_query_result = $step3_select_query->execute(); 
    
         $result_step3=$step3_select_query_result->fetchAssoc();



                     $content .= '<div><b> 3.Accidents & Dangerous Occurrences </b></div>

                     <table width="100%" border="1"   >

                                          <tr>
                                                        <th colspan="4" align="center" valign="middle" >No. Of Accidents</th>
                                                        <th colspan="4" align="center" valign="middle">No. of dangerous occurrences</th>
                                                        <th colspan="8" align="center" valign="middle">No. of visits paid in connection with</th>
                                                        
                                                      
                                                      
                                                    </tr>
                                                
                                                    <tr>
                                                        <th  align="center" valign="middle" >Fatal</th>
                                                        <th  align="center" valign="middle">Serious</th>
                                                        <th  align="center" valign="middle">Explosion</th>
                                                        <th  align="center" valign="middle">Fire</th>

                                                        <th  align="center" valign="middle">Gassing</th>
                                                        <th  align="center" valign="middle">Toxic Release</th>
                                                        <th  align="center" valign="middle">Collapse</th>
                                                        <th  align="center" valign="middle">Others</th>

                                                        <th  align="center" valign="middle">Fatal accident</th>
                                                        <th  align="center" valign="middle">Serious accident</th>
                                                        <th  align="center" valign="middle">Explosion</th>
                                                        <th  align="center" valign="middle">Fire</th>

                                                        <th  align="center" valign="middle">Gassing</th>
                                                        <th  align="center" valign="middle">Toxic release</th>
                                                        <th  align="center" valign="middle">Collapse</th>
                                                        <th  align="center" valign="middle">Others</th>
                                                      
                                                      
                                                    </tr>


                                                

                                                   <tr>
                                                       
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_pwa'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_mba'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_msihcr'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_car'].' </td>
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_clpra'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_rest_interval'].'</td>
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_bef_after_legal_hours'].' </td>  
                                                        <td  align="center" valign="middle"> '.$result_step3['visit_sunday_holiday'].'</td>

                                                          <td  align="center" valign="middle"> '.$result_step3['visit_approval_of_plan'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step3['visit_reg_licence'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step3['visit_collection_statistics'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step3['visit_enq_complaints'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step3['visit_court_attendance'].'</td>
                                                          <td  align="center" valign="middle"> '.$result_step3['visit_attn_seminar_meeting'].'</td>
                                                         <td  align="center" valign="middle"> '.$result_step3['visit_to_closed_factory'].'</td>
                                                         <td  align="center" valign="middle"> '.$result_step3['visit_others'].'</td>
                                                        
                                                    </tr>


                      </table>

                <div><b> 4(a). Detail of fatal & serious accidents </b></div>

                      ';

                      $query_step4_a=db_query('select  *  from labour_factory_statcell_form_5_t4a a , labour_factory_accident_classification_mst b  where CAST (a.classification_code AS INTEGER)=b.accident_classification_id and   monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
     
     $content .= '<table cellpadding="0" cellspacing="0" border="0" class="add-employee-table-view" width="100%">
      <tr > 
      
       <th > Name of the Factory</th>
      <th >Address of the Factory</th>
       
     <th >Name(s) of the deceased / injured</th>

     <th >Date of accident</th>
       
     <th >Accident classification</th>
     
   
    </tr>';  
        $i=0;
    foreach($query_step4_a as $squan) {
      $i++;
          $acc_details_id = $squan->acc_details_id; 
          $monthly_form_id = $squan->monthly_form_id; 
          $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
                 $content .= "<tr>";
                $content.= "<td>".$acc_det_name_of_factory."</td>";
                $content.= "<td>".$squan->acc_det_address_of_factory."</td>";
                $content.= "<td>".$squan->acc_det_name_of_deceased_injured."</td>";
                $content.= "<td>".date('d-m-Y', strtotime($squan->acc_det_date_of_accident))."</td>";

                 $content.= "<td>".$squan->classification_class.'-'.$squan->classification_details."</td>";
                
                
                $content.= "<td >".$del_preper."</td>";
      
              
              $content .= "</tr>";
            }
              $content .= "</table>

                 <div><b> 4(b). Detail of Non fatal accidents </b></div>

              ";
                $query_tab_4_b=db_query('select  *  from labour_factory_statcell_form_5_t4b a , labour_factory_accident_classification_mst b  where CAST (a.classification_code AS INTEGER)=b.accident_classification_id and   monthly_form_id = :anid', array(':anid' => trim($filenumber) ));


           $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > 
      
       <th > Accident classification</th>
      <th >Type of Industry </th>
       
     <th >Adult Male</th>

     <th >Adult Female</th>
       
     <th >Adolescent Male</th>
     
     <th >Adolescent Female</th>
    <th >Child Male</th>
    <th >Child Female</th>
    
    </tr>";  
        $i=0;
    foreach($query_tab_4_b as $squan) {
      $i++;
         // $acc_details_id = $squan->acc_details_id; 
          $monthly_form_id = $squan->monthly_form_id; 
            $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
       

              
              
              
      

        
       
     
              $content.= "<td>".$squan->classification_class.'-'.$squan->classification_details."</td>";
              $content.= "<td>".$squan->type_of_industry."</td>";
              $content.= "<td>".$squan->injured_adult_male."</td>";
              $content.= "<td>".$squan->injured_adult_female."</td>";

              $content.= "<td>".$squan->injured_ado_male."</td>";
              $content.= "<td>".$squan->injured_ado_female."</td>";

              $content.= "<td>".$squan->injured_child_male."</td>";
              $content.= "<td>".$squan->injured_child_female."</td>";
                
                
                
               
      
              
              $content .= "</tr>";
            }
              $content .= "</table>

              <div><b> 5. Notifiable diseases / Cases of Poisoning </b></div>

              ";

$query_step5=db_query('select  *  from labour_factory_statcell_form_5_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
     
     $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      <th >Nature of Mfg. process</th>
       
     <th >Name of persons involved</th>

     <th >Occupation</th>
       
     <th >Name of the disease / poison</th>
      <th >Action Taken/ Remarks</th>
       
     
    
    </tr>";  
        $i=0;
    foreach($query_step5 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->notifiable_desease_id; 
           
              
              
      

        
        //$output1.= "<td>".$i."</td>"; 
                $content.= "<td>".$squan->nd_name_of_factory."</td>";
                $content.= "<td>".$squan->nd_address_of_factory."</td>";
                $content.= "<td>".$squan->nd_nature_mfg_process."</td>";
                $content.= "<td>".$squan->nd_persons_involved."</td>";
                
             
                $content.= "<td>".$squan->nd_occupation."</td>";
                $content.= "<td>".$squan->nd_name_of_disease."</td>";
                $content.= "<td >".$squan->nd_action_remarks."</td>";
        
       
        $content.= "<td >".$del_preper."</td>";
      
              
         $content .= "</tr>";
            }
        $content .= "</table>

        <div><b> 6. Chemical Factories </b></div> ";

 $query_step6=db_query('select  *  from labour_factory_statcell_form_5_t6_6_t3 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
      $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr> <th rowspan='2' >Name of the Factory</th>
      
       <th rowspan='2' > Address of the Factory</th>
       <th colspan='2' > Raw Materials Used</th>
       <th colspan='2' > Intermediaries</th>
       <th colspan='2' > Products Manufactured</th>

      <th rowspan='2' >Possible Hazards</th>
      <th rowspan='2' >Action Taken / Remarks</th>
    </tr>
    <tr>
      <th >Name</th>
       
     <th >Max. Qty. Stored</th>

    

     <th >Name</th>
     <th >Max. Qty. Stored</th>
       
      <th >Name</th>
      <th >Max. Qty. Stored</th>

     
       
     
   
    </tr>";  
        $i=0;
    foreach($query_step6 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->chem_fac_id; 
           
              
              
      

       
             
               $content .= "<tr >";
        
        
        
                $content.= "<td>".$squan->chem_fac_name_of_factory."</td>";
                $content.= "<td>".$squan->chem_fac_address_of_factory."</td>";
                $content.= "<td>".$squan->chem_fac_raw_mat_name."</td>";
                $content.= "<td>".$squan->chem_fac_raw_mat_quantity."</td>";
                
             
                $content.= "<td>".$squan->chem_fac_intermediaries_name."</td>";
                $content.= "<td>".$squan->chem_fac_intermediaries_quantity."</td>";

                $content.= "<td>".$squan->chem_fac_products_name."</td>";
                $content.= "<td>".$squan->chem_fac_products_quantity."</td>";

                $content.= "<td>".$squan->chem_fac_possible_hazards."</td>";
                $content.= "<td>".$squan->chem_fac_action_remarks."</td>";
        
       
      
      
              
               $content .= "</tr>";
            }
              $content .= "</table>

              <div><b> 7. Orders issued under various Acts & Rules </b></div>


              ";
        
      $query_step7=db_query('select  *  from labour_factory_statcell_form_5_t7 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
       $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      <th >Act and S/R under which the order was issued</th>
       
     <th >Time allowed</th>

    

     <th >Brief description including results (attach copies)</th>
    
       
     
    
    </tr>";  
        
    foreach($query_step7 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->ord_id; 
           
              
              
      

         
                $content .= "<tr >";
        
      
                $content.= "<td>".$squan->factory_name."</td>";
                $content.= "<td>".$squan->factory_address."</td>";
                $content.= "<td>".$squan->acts_issued."</td>";
                $content.= "<td>".$squan->time_allowed."</td>";
                $content.= "<td>".$squan->result_description."</td>";
               
                $content .= "</tr>";
                
        
            }
              $content .= "</table>

            <div><b> 8. Complaints </b></div>
              ";
       
            
      
              
         $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th rowspan='2' >Factory</th>

        <th colspan='6' align='center' valign='middle' >Registered</th>
       <th colspan='6' align='center' valign='middle' >Unregistered</th> </tr>
      <tr>
       <th> FA</th>
       <th> PWA</th>
      <th> MBA</th>
      <th> MSIHCR</th>
      <th> CAR</th>
      <th> CL(P&R)A</th>
      <th> FA</th>
      <th> PWA</th>
      <th> MBA</th>
      <th> MSIHCR</th>
      <th> CAR</th>
      <th> CL(P&R)A</th>
       
     
    
    </tr>"; 
  

      $step8_select_query = db_select('labour_factory_statcell_form_5_t8', 'a');
       
        $step8_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step8_select_query->fields('a',array('compl_reg_no_rec_fa' ,
    'compl_reg_no_rec_pwa' ,
    'compl_reg_no_rec_mba' ,
    'compl_reg_no_rec_msihcr' ,
    'compl_reg_no_rec_car' ,
    'compl_reg_no_rec_clpra',
    'compl_unreg_no_rec_fa',
    'compl_unreg_no_rec_pwa',
    'compl_unreg_no_rec_mba',
    'compl_unreg_no_rec_msihcr' ,
    'compl_unreg_no_rec_car' ,
    'compl_unreg_no_rec_clpra',
    'compl_reg_no_inv_fa',
    'compl_reg_no_inv_pwa',
    'compl_reg_no_inv_mba' ,
    'compl_reg_no_inv_msihcr',
    'compl_reg_no_inv_car',
    'compl_reg_no_inv_clpra',
    'compl_unreg_no_inv_fa',
    'compl_unreg_no_inv_pwa' ,
    'compl_unreg_no_inv_mba',
    'compl_unreg_no_inv_msihcr' ,
    'compl_unreg_no_inv_car' ,
    'compl_unreg_no_inv_clpra',
    'compl_reg_no_settled_fa',
    'compl_reg_no_settled_pwa' ,
    'compl_reg_no_settled_mba',
    'compl_reg_no_settled_msihcr',
    'compl_reg_no_settled_car',
    'compl_reg_no_settled_clpra' ,
    'compl_unreg_no_settled_fa' ,
    'compl_unreg_no_settled_pwa' ,
    'compl_unreg_no_settled_mba' ,
    'compl_unreg_no_settled_msihcr',
    'compl_unreg_no_settled_car',
    'compl_unreg_no_settled_clpra',
    'compl_reg_violation_fa' ,
    'compl_reg_violation_pwa' ,
    'compl_reg_violation_mba',
    'compl_reg_violation_msihcr' ,
    'compl_reg_violation_car' ,
    'compl_reg_violation_clpra',
    'compl_unreg_violation_fa' ,
    'compl_unreg_violation_pwa' ,
    'compl_unreg_violation_mba' ,
    'compl_unreg_violation_msihcr' ,
    'compl_unreg_violation_car' ,
    'compl_unreg_violation_clpra',
    'compl_reg_remarks_fa' ,
    'compl_reg_remarks_pwa' ,
    'compl_reg_remarks_mba' ,
    'compl_reg_remarks_msihcr',
    'compl_reg_remarks_car' ,
    'compl_reg_remarks_clpra' ,
    'compl_unreg_remarks_fa' ,
    'compl_unreg_remarks_pwa' ,
    'compl_unreg_remarks_mba' ,
    'compl_unreg_remarks_msihcr',
    'compl_unreg_remarks_car',
    'compl_unreg_remarks_clpra' ));
    $step8_select_query_result = $step8_select_query->execute(); 
    
    $result_step8=$step8_select_query_result->fetchAssoc();

                $content .= "<tr >";
        
                $content.= "<td>No. Received</td>";
                $content.= "<td>".$result_step8['compl_reg_no_rec_fa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_rec_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_rec_mba']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_rec_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_rec_car']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_rec_clpra']."</td>";

                $content.= "<td>".$result_step8['compl_unreg_no_rec_fa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_rec_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_rec_mba']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_rec_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_rec_car']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_rec_clpra']."</td>";
              

               
               $content .= "</tr>";


               $content .= "<tr >";
        
                $content.= "<td>No. investigated</td>";
                $content.= "<td>".$result_step8['compl_reg_no_inv_fa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_inv_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_inv_mba']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_inv_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_inv_car']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_inv_clpra']."</td>";

                $content.= "<td>".$result_step8['compl_unreg_no_inv_fa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_inv_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_inv_mba']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_inv_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_inv_car']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_inv_clpra']."</td>";
              

               
               $content .= "</tr>";


               $content .= "<tr >";
        
                $content.= "<td>No. settled</td>";
                $content.= "<td>".$result_step8['compl_reg_no_settled_fa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_settled_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_settled_mba']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_settled_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_settled_car']."</td>";
                $content.= "<td>".$result_step8['compl_reg_no_settled_clpra']."</td>";

                $content.= "<td>".$result_step8['compl_unreg_no_settled_fa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_settled_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_settled_mba']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_settled_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_settled_car']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_no_settled_clpra']."</td>";
              

               
               $content .= "</tr>";

               $content .= "<tr >";
        
                $content.= "<td>Violation observed</td>";
                $content.= "<td>".$result_step8['compl_reg_violation_fa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_violation_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_violation_mba']."</td>";
                $content.= "<td>".$result_step8['compl_reg_violation_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_reg_violation_car']."</td>";
                $content.= "<td>".$result_step8['compl_reg_violation_clpra']."</td>";

                $content.= "<td>".$result_step8['compl_unreg_violation_fa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_violation_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_violation_mba']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_violation_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_violation_car']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_violation_clpra']."</td>";
              

               
               $content .= "</tr>";

               $content .= "<tr >";
        
                $content.= "<td>Remarks</td>";
                $content.= "<td>".$result_step8['compl_reg_remarks_fa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_remarks_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_reg_remarks_mba']."</td>";
                $content.= "<td>".$result_step8['compl_reg_remarks_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_reg_remarks_car']."</td>";
                $content.= "<td>".$result_step8['compl_reg_remarks_clpra']."</td>";

                $content.= "<td>".$result_step8['compl_unreg_remarks_fa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_remarks_pwa']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_remarks_mba']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_remarks_msihcr']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_remarks_car']."</td>";
                $content.= "<td>".$result_step8['compl_unreg_remarks_clpra']."</td>";
              

               
               $content .= "</tr></table>

              <div><b> 9. Prosecution Proceedings instituted </b></div>";


             

        $query_step9=db_query('select  *  from labour_factory_statcell_form_5_t9_7_t6 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));        
      $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      <th >Registered/Unregistered</th>
       
     <th >Person Prosecuted (Occupier, Manager etc)</th>

    

     <th >Case No.</th>
      <th >Name of the act.</th>
      <th >Violation.</th>
      <th >Penal Provision</th>
      <th >Name of the Court</th>
      <th >Remarks / Result</th>
    
       
     
    
    </tr>";  
     
    foreach($query_step9 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->pros_instituted_id; 
         
           
              $content .= "<tr >";
       
      
                $content.= "<td>".$squan->pros_instituted_name_of_factory."</td>";
                $content.= "<td>".$squan->pros_instituted_address_of_factory."</td>";
                $content.= "<td>".$squan->pros_instituted_reg_unreg."</td>";
                $content.= "<td>".$squan->pros_instituted_person_prosecuted."</td>";
                $content.= "<td>".$squan->pros_instituted_case_no."</td>";
                $content.= "<td>".$squan->pros_instituted_name_of_act."</td>";
                $content.= "<td>".$squan->pros_instituted_violation."</td>";
                $content.= "<td>".$squan->pros_instituted_penal_provision."</td>";
                $content.= "<td>".$squan->pros_instituted_name_of_court."</td>";
                $content.= "<td>".$squan->pros_instituted_remarks_result."</td>";
              
               $content .= "</tr>";
            }
                
        
       
            
      
              
         
              $content .= "</table>

               <div><b> 10.  Particulars of the cases disposed off </b></div>";


 $query_step10=db_query('select  *  from labour_factory_statcell_form_5_t10_7_t7 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
     
     $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Person Prosecuted (Occupier, Manager etc)</th>

    

     <th >Case No.</th>
      <th >Name of the act.</th>
      <th >Violation.</th>
      <th >Result/ Amount of the fine</th>
      <th >Date of disposal</th>
      <th >Name of the Court</th>
      <th >Remarks / Result</th>
    
       
     
    
    </tr>";  
       
    foreach($query_step10 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->case_disposed_id; 
         
           
              
              
      

        
        
        
          
                 $content .= "<tr>";
        
                $content.= "<td>".$squan->case_disposed_name_of_factory."</td>";
                $content.= "<td>".$squan->case_disposed_address_of_factory."</td>";
                $content.= "<td>".$squan->case_disposed_person_prosecuted."</td>";
                $content.= "<td>".$squan->case_disposed_case_no."</td>";
                $content.= "<td>".$squan->case_disposed_name_of_act."</td>";
                $content.= "<td>".$squan->case_disposed_violation."</td>";
                $content.= "<td>".$squan->case_disposed_result_fine."</td>";
                $content.= "<td>".$squan->case_disposed_date_of_disposal."</td>";
                $content.= "<td>".$squan->case_disposed_name_of_court."</td>";
                $content.= "<td>".$squan->case_disposed_remarks_result."</td>";
                $content .= "</tr>";
               
           
        
            }
              $content .= "</table>
              ";



        $step11_select_query = db_select('labour_factory_statcell_form_5', 'a');
       
        $step11_select_query->condition('a.monthly_form_id',trim($filenumber),'=');
      
    
        $step11_select_query->fields('a',array('appeal_to_high_court','other_mat_special_interest'));
        
        $step11_select_query_result = $step11_select_query->execute(); 
    
       $result_step11=$step11_select_query_result->fetchAssoc();
     



 $content .= "<table width='100%' border='1'   >
                                                
                                                    <tr>
                                                        <th  align='center' valign='middle' > 11. Particulars of Appeal to High Court</th>
                                                        <th  align='center' valign='middle'>14. Other matters of special interest </th>
                                                      
                                                    </tr>


                                             <tr>
                                                        
                                                        
                                                        <td  align='left' valign='middle'> ".$result_step11['appeal_to_high_court']."</td>   
                                                        <td  align='left' valign='middle'>".$result_step11['other_mat_special_interest']." </td>
                                                        
                                                      
                                                    </tr>
     </table>";


              
      $query_step12=db_query('select  *  from labour_factory_statcell_form_5_t12_6_t5_7_t5 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));

          $content .= "
               <div><b> 12. Details of Seminars/Training Courses etc. </b></div>

          <table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Type of program</th>

    

     <th >Date of program</th>
      <th >No. of participants</th>
      <th >Status of participants</th>
    
    </tr>";  
      
    foreach($query_step12 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->seminar_id; 
         
        
            
              $content .= "<tr >";
      
      
                $content.= "<td>".$squan->seminar_name_of_factory."</td>";
                $content.= "<td>".$squan->seminar_address_of_factory."</td>";
                $content.= "<td>".$squan->seminar_type_of_program."</td>";
                $content.= "<td>".$squan->seminar_date_of_program."</td>";
                $content.= "<td>".$squan->seminar_no_of_participants."</td>";
                $content.= "<td>".$squan->seminar_status_of_participants."</td>";
             
           
              
         $content .= "</tr>";
            }
        $content .= "</table>

         <div><b> 13. Application Filled before the Authority under the P.W. Act </b></div> ";


$query_step13=db_query('select  *  from labour_factory_statcell_form_5_t13 where  monthly_form_id = :anid', array(':anid' => trim($filenumber) ));
       
 $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>
      <tr > <th >Name of the Factory</th>
      
       <th > Address of the Factory</th>
      
       
     <th >Type of program</th>

    

     <th >No. of Persons involved</th>
    <th >Unpaid wages claimed</th>
    <th >Unauthorized deduction claimed</th>
    <th >Remarks</th>
    
       
     
     
    </tr>";  
       
    foreach($query_step13 as $squan) {
      $i++;
          
          $monthly_form_id = $squan->monthly_form_id; 
          $row_id = $squan->pw_act_id; 
         
           
              
              
      

        
                 $content .= "<tr >";
         
      
                $content.= "<td>".$squan->pw_act_name_of_factory."</td>";
                $content.= "<td>".$squan->pw_act_address_of_factory."</td>";
                $content.= "<td>".$squan->pw_act_case_no."</td>";
                $content.= "<td>".$squan->pw_act_persons_involved."</td>";
                $content.= "<td>".$squan->pw_act_amount_unpaid_wages."</td>";
                $content.= "<td>".$squan->pw_act_amount_unauthorized_deduction."</td>";
                $content.= "<td>".$squan->pw_act_remarks."</td>";
              
               
                 $content .= "</tr>";
        
       
            
      
              
        
            }
             $content .= "</table>


             <div><b> 14. BOCW Act </b></div>"; 

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
             
   $content .= "<table cellpadding='0' cellspacing='0' border='0' class='add-employee-table-view' width='100%'>";
   $content .="<tr ><td>1.No. of Units visited </td> <td> ".$result_step14['no_of_units_visit']."</td></tr>";
   $content .= "<tr ><td> a)  for general </td> <td> ".$result_step14['no_of_visit_paid_general']."</td></tr>";
   $content .= "<tr ><td> b)  for complaint </td> <td> ".$result_step14['no_of_visit_paid_complaint']."</td></tr>";
    $content .= "<tr ><td>  c)  for accident </td> <td> ".$result_step14['no_of_visit_paid_accident']."</td></tr>";
   $content .= "<tr ><td>3.  No. of complains received </td> <td> ".$result_step14['no_of_complaints_received']."</td></tr>";  
   $content .= "<tr ><td>4.  Details of the complaint with violation, if any </td> <td> ".$result_step14['details_of_complaint']."</td></tr>";       
  $content .= "<tr ><td>5. No. of accidents reported </td> <td> ".$result_step14['no_of_accidents_reported']."</td></tr>";   
  $content .= "<tr ><td>  a)  Name of I.P/deceased </td> <td> ".$result_step14['accident_details_name_of_deceased']."</td></tr>";             
  $content .= "<tr ><td>  b)  Age </td> <td> ".$result_step14['accident_details_age']."</td></tr>";
  $content .= "<tr ><td>c)  Sex </td> <td> ".$result_step14['accident_details_sex']."</td></tr>";
  $content .= "<tr ><td>  d)  Dt. & time of accident </td> <td> ".$result_step14['accident_details_date_of_accident']."</td></tr>";
 $content .= "<tr ><td> e)  Nature of accident (serious/Fatal) </td> <td> ".$result_step14['accident_details_nature_of_accident']."</td></tr>";
  $content .= "<tr ><td>  f)  Brief description of accident with violation, if any </td> <td> ".$result_step14['accident_details_description']."</td></tr>";

  $content .= "<tr ><td>    g)  Place of accident </td> <td> ".$result_step14['accident_details_place']."</td></tr>";
  $content .= "<tr ><td>    h)  Name of employer </td> <td> ".$result_step14['accident_details_name_of_employer']."</td></tr>";
  $content .= "<tr ><td>    i)  Address of the site</td> <td> ".$result_step14['accident_details_address_of_site']."</td></tr>";
  $content .= "<tr ><td>    7. Details of violation in general visit (S/R)</td> <td> ".$result_step14['details_of_violation_general_visit']."</td></tr>";
  $content .= "<tr ><td>    a)  In connection with general visit</td> <td> ".$result_step14['no_of_prosecution_general_visit']."</td></tr>";
  $content .= "<tr ><td>    b)  In connection with complaint enquiry</td> <td> ".$result_step14['no_of_prosecution_complaint']."</td></tr>";
  $content .= "<tr ><td>   c)  In connection with accident enquiry</td> <td> ".$result_step14['no_of_prosecution_accident']."</td></tr>";

   $content .= "<tr ><td colspan='2'>  8 No. of prosecution</td></tr>";

  $content .= "<tr ><td>   a) Violation (S/R)</td> <td> ".$result_step14['details_of_prosecution_violation']."</td></tr>";
  $content .= "<tr ><td>    b)  Name of the Court</td> <td> ".$result_step14['details_of_prosecution_court_name']."</td></tr>";
  $content .= "<tr ><td>    c)  Case No</td> <td> ".$result_step14['details_of_prosecution_case_no']."</td></tr>";

  $content .= "<tr ><td>      d)  Result / Remarks</td> <td> ".$result_step14['details_of_prosecution_result']."</td></tr>";
  $content .= "<tr ><td>    10  Any other information</td> <td> ".$result_step14['other_information']."</td></tr>";
   $content .= "</table>";
       

             }  

        $form['step17field']['colcontent'] = array
              (
                 '#prefix' => ' <div   >'.$content, 
               
           

                '#suffix'=>'</div>',
       
       
           );


              $result_string = "'".str_replace(",", "','", $area)."'";

            
             $roleId=get_role_id($inspector_id);
           
             $role_name=get_role_name($roleId);
             //print 'sss'.$role_name.'fff'.$roleId;
             if($role_name=='factoryinspector')
                $deputy_cheif_role='deputychief';
             elseif($role_name=='factoryinspector_chemical')
                $deputy_cheif_role='deputychief_chemical';
            elseif($role_name=='factoryinspector_medical')
                $deputy_cheif_role='deputychief_medical';

              //print 'sss'.$role_name.'=='.$deputy_cheif_role.'=='.$result_string;

             
               //print $result_string;


           $options_dp =  monthly_rep_deputy_director_option($result_string , $deputy_cheif_role );
         
          $form['step17field']['dp_director'] = array (
                    '#type' => 'select',
                    '#title' => ('Select Deputy'),
                    '#options'       => $options_dp,
                    
                    '#required' => TRUE,
                   //  '#multiple'     =>  true,
                   //   '#attributes' => array('style' => array('height: 100px; ')),
                
                   '#prefix'            => '<div class="col-sm-3"       > ',
                   '#suffix'            => '</div>',
                    //'#rows'        => 10,
               );

     $form['step17field']['submit_button']                    = array(
                                                                 
                                                               '#prefix' => '<div style="text-align:center;" >',
                                                                 '#suffix'=>'</div>', 
                                                                '#type'                 =>'submit',
                                                                '#value'                =>t(' Submit ')
                                                                );

      return $form;

    }

function month_report_step17_submit($form, &$form_state) {
   global $base_root, $base_path,$full_base;

      $full_base='';


      $val=$form_state['values'];
       //print_r($val);
       //exit;


    $monthlyformid=trim($val['monthlyformid']);
    $dp_director=trim($val['dp_director']);

    $txn = db_transaction();
      try {
          
   


      $query_update_B = db_update('labour_factory_statcell_form_5');
      $query_update_B->fields(array(
    'submit_date' => date("Y-m-d")  ,'is_submitted' => 1 , 'accept_by' => $dp_director , 'create_date' => date("Y-m-d") , 'status' => 'FD'));
                                        
                                        
                                        
       $query_update_B->condition('monthly_form_id',$monthlyformid);
       $query_update_B->execute(); 





    
    
       $message = '   monthly report submit successfully ';
     drupal_set_message(t($message));
     $full_base=$base_root.$base_path.'admin/monthly-report-list';
               
    drupal_goto($full_base);
    
     }
    catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
    $message = '    monthly report is not submit  ';
     drupal_set_message(t($message));

      $full_base=$base_root.$base_path.'admin/annual-report/step17/'.$autoGENNO;
               
    drupal_goto($full_base);
     }


}    


function monthly_rep_deputy_director_option($area , $deputy_cheif_role) {
   

   $blk=" select DISTINCT u.uid, fzum.zone_id, zone_name, fname, r.name
from fa_zone_user_map fzum
inner join users u on fzum.uid = u.uid
inner join users_roles ur on u.uid = ur.uid
inner join role r on ur.rid = r.rid
inner join fa_employee_details ed on u.uid = ed.uid
inner join fa_zone fz on fzum.zone_id = fz.zone_id and u.status=1 and ed.status=1
where r.name = '".$deputy_cheif_role."' and fz.zone_name in (".$area.")";
//print $blk;
//exit;
    
    $state_query=db_query($blk);

  $options              = array();
    
    foreach($state_query as $state_result) {
        
        $options[$state_result->uid] =$state_result->fname;  
    
    }
    
    
    
   
       return $options;
        
  
      
    
    
}
//and u.status=1 and ed.status=1