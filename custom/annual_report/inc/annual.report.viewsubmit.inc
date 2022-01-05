<?php
function annual_report_view($form, &$form_state, $id= NULL) {
	 global $base_root, $base_path;

	// require_once $_SERVER['DOCUMENT_ROOT'].$base_path.'sites/all/modules/contrib/pdf_using_mpdf/mpdf/mpdf.php';
	 
     $filenumber= encryption_decryption_fun('decrypt', trim($id));
    // $id=5;
	 //$filenumber=  trim($id);
     //print "aaaaaaaaaaaaaaaaaa".$filenumber;
     //exit;

	
		
		$content = '<style type="text/css">
          
          .data{ text-transform: uppercase;font-weight:bold;}
          
      </style>';
      $mr_istquery = db_select('labour_factory_statcell_annual_report', 'a');
       
        $mr_istquery->condition('a.annual_inspection_id',trim($filenumber),'=');
      
    
        $mr_istquery->fields('a',array('area','inspector_id','annual_form_type','report_from_date','report_to_date','report_year'));
        $mr_istquery_result = $mr_istquery->execute(); 
    
       $result_mrist=$mr_istquery_result->fetchAssoc();
       $area=$result_mrist['area'];
       $inspector_id=$result_mrist['inspector_id'];
       //$inspector_name=get_name($inspector_id);
      $annual_form_type=$result_mrist['annual_form_type'];
      $report_from_date=$result_mrist['report_from_date'];
       $report_to_date=$result_mrist['report_to_date'];
      $thisYear=$result_mrist['report_year'];

    $query_uname=db_query('select fname from fa_employee_details where uid = :fuid  ', array(':fuid' => trim($inspector_id)));
    $inspector_name='';
    if($query_uname->rowCount() > 0)
     $inspector_name=get_name($inspector_id);
    else
    {
    
    $query_newinsid=db_query('select fa_uid  from tm_users where old_uid = :ouid  ', array(':ouid' => trim($inspector_id)));

    $result_newinsId=$query_newinsid->fetchAssoc();
    $inspector_id = $result_newinsId['fa_uid']; 
    $inspector_name=get_name($inspector_id);

    }

$content = '<table width="100%" >				
					<tr><td colspan="3"></td></tr>				
					<tr><td colspan="3" align="center" style="font-size:20px;text-transform:uppercase;"><h4><b>Annual Report</b></h4></td></tr>
					<tr><td colspan="3" align="center" style="font-size:16px;text-transform:uppercase;"><span style="color: #045541;"><b>Name of the Inspector: '.$inspector_name.', Area:'.$area.'</b></span></td></tr>
                    <tr><td colspan="3" align="center" style="font-size:16px;text-transform:uppercase;"><span style="color: #045541;"><b>Report For: '.$annual_form_type.', From Date:'.date('d-m-Y', strtotime($report_from_date)).' , To:'.date('d-m-Y', strtotime($report_to_date)).'</b></span></td></tr>
					<tr><td colspan="3"></td></tr></table>';

	

	$content .= ' 
    <div class="table-panel-header"><b>1.INSPECTION ETC. </b></div>
	<div><b>(a). No. of units visited</b> </div>
	<div class="table-responsive">
	<table class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                <thead>
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
                                                      
                                                    </tr></thead>';

        $step1_select_query = db_select('labour_factory_statcell_annual_report_t1_a_b', 'a');
       
        $step1_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
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
                                                   
                                                    </table></div>

                                                    <div class="table-panel-header"><b>(b). No. of visits paid to </b></div>
													<div class="table-responsive">
                                                    <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                                	<thead>
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
                                                      
                                                    </tr></thead>

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
                                                   
                                                    </table></div>
                                                    <div class="table-panel-header"><b>C.Frequency of Visit </b></div>
                                                    <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                                	<thead>
                                                    <tr>
                                                        <th rowspan="2" align="center" valign="middle" >Frequency</th>
                                                        <th colspan="2" align="center" valign="middle">Factories other than defence installations</th>
                                                        <th colspan="2" align="center" valign="middle">Defence Installation</th>
                                                        <th colspan="2" align="center" valign="middle">Total</th>
                                                      
                                                    </tr>

                                                    <tr>
                                                        <th  align="center" valign="middle" >Regd.</th>
                                                        <th  align="center" valign="middle">Un-registered (Amenable & Non-Amenable).</th>
                                                        <th  align="center" valign="middle">Regd..</th>
                                                        <th  align="center" valign="middle">Un-registered (Amenable & Non-Amenable).</th>
                                                        <th  align="center" valign="middle">Regd...</th>
                                                        <th  align="center" valign="middle">Un-registered (Amenable & Non-Amenable).</th>
                                                      
                                                    </tr></thead>';

                                                     $query_tab_1_c=db_query('select  *  from labour_factory_statcell_annual_report_t1_c where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
                                                      foreach($query_tab_1_c as $squan) {
                                                      $i++;
                                                      $row_id = $squan->row_id; 
                                                      $annual_inspection_id = $squan->annual_inspection_id; 
                                                      $frequency=$squan->frequency;
                                                       if($frequency==1)
                                                        $frequency='once';
                                                       elseif($frequency==2)
                                                         $frequency='twice';
                                                        elseif($frequency==3)
                                                         $frequency='thrice';
                                                        elseif($frequency==4)
                                                         $frequency='four times'; 
                                                       elseif($frequency==5)
                                                         $frequency='five times';
                                                     elseif($frequency==6)
                                                         $frequency='six times';
                                                     elseif($frequency==7)
                                                         $frequency='More than six times';

                                                      $not_defence_reg=$squan->not_defence_reg;
                                                      $not_defence_unreg=$squan->not_defence_unreg;
                                                      $defence_reg=$squan->defence_reg;

                                                      $defence_unreg=$squan->defence_unreg;

                                                       $total_reg=$squan->total_reg;
                                                       $total_unreg=$squan->total_unreg;

                                                     $content .= ' <tr>
                                                       
                                                        <td  align="center" valign="middle">'.$frequency.' </td>
                                                        <td  align="center" valign="middle">'.$not_defence_reg.' </td>
                                                        <td  align="center" valign="middle">'.$not_defence_unreg.' </td>
                                                        <td  align="center" valign="middle">'.$defence_reg.' </td>
                                                        <td  align="center" valign="middle">'.$defence_unreg.' </td>
                                                        <td  align="center" valign="middle">'.$total_reg.' </td>
                                                        <td  align="center" valign="middle">'.$total_unreg.' </td> 	
                                                        
                                                      
                                                    </tr>';
                                                }
                                                 $content .= '</table></div>
                                                 <div class="table-panel-header"><b>D.No. of Visits paid. </b></div>
												 <div class="table-responsive">
                                                  <table  class="table table-striped table-bordered table-responsive admin-custom-table">
                                                	<thead>
                                                    <tr>
                                                        <th colspan="5" align="center" valign="middle" >Exclusive Under</th>
                                                        <th rowspan="2" align="center" valign="middle">During Rest Interval</th>
                                                        <th rowspan="2" align="center" valign="middle">Before or after legal hours</th>
                                                        <th rowspan="2" align="center" valign="middle">On Sundays/Holidays</th>
                                                        <th rowspan="2" align="center" valign="middle">For approval of plans</th>
                                                        <th rowspan="2" align="center" valign="middle">For Renewal of licence</th>
                                                      
                                                    </tr>

                                                    <tr>
                                                        <th  align="center" valign="middle" >MSIHCR.</th>
                                                        <th  align="center" valign="middle">P.W.A.</th>
                                                        <th  align="center" valign="middle">M.B.A</th>
                                                        <th  align="center" valign="middle">C.A.R..</th>
                                                        <th  align="center" valign="middle">C.I.(P&R)A</th>
                                                      
                                                      
                                                    </tr></thead>';
                                                    $step1_select_B_query = db_select('labour_factory_statcell_annual_report_t1_d', 'b');
       
                                                    $step1_select_B_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
        
                   $step1_select_B_query->fields('b',array('visit_msihcr','visit_pwa','visit_mba','visit_car','visit_clpra','visit_rest_interval','visit_bef_after_legal_hours','visit_sunday_holiday', 'visit_approval_of_plan','visit_renew_licence','visit_collection_statistics','visit_enq_complaints','visit_court_prosecution','visit_to_closed_factory','visit_others','visit_total'));
                                                  $step1_select_B_query_result = $step1_select_B_query->execute(); 
        
                                                  $result_step1_B=$step1_select_B_query_result->fetchAssoc();
                                                  $visit_msihcr=$result_step1_B['visit_msihcr'];
                                                  $content .= ' <tr>
                                                       
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_msihcr'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_pwa'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_mba'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_car'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_clpra'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_rest_interval'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_bef_after_legal_hours'].' </td> 	
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_sunday_holiday'].' </td> 
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_approval_of_plan'].' </td> 
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_renew_licence'].' </td> 
                                                    </tr>

                                                    <tr>
                                                        <th  colspan="2" valign="middle" style="text-align:center;">For collections of statistics.</th>
                                                        <th  colspan="2" align="center" style="text-align:center;">For enquiry into complaints</th>
                                                        <th  colspan="2" align="center" style="text-align:center;">To court for prosecution cases</th>
                                                        <th  colspan="2" align="center" style="text-align:center;">To closed factories</th>
                                                        <th  align="center" style="text-align:center;">Others</th>
                                                        <th   align="center" style="text-align:center;">Total</th>
                                                      
                                                    </tr>
                                                     <tr>
                                                       
                                                        <td  colspan="2" align="center" valign="middle">'.$result_step1_B['visit_collection_statistics'].' </td>
                                                        <td  colspan="2" align="center" valign="middle">'.$result_step1_B['visit_enq_complaints'].' </td>
                                                        <td  colspan="2" align="center" valign="middle">'.$result_step1_B['visit_court_prosecution'].' </td>
                                                        <td  colspan="2" align="center" valign="middle">'.$result_step1_B['visit_to_closed_factory'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_others'].' </td>
                                                        <td  align="center" valign="middle">'.$result_step1_B['visit_total'].' </td>
                                                         	
                                                        
                                                      
                                                    </tr>
                                                </table></div>
                                                 <div class="table-panel-header"><b>2(A) Accident and Dangerous occurrances </b></div>
                                                 <div class="table-responsive">
  													<table class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                	`<thead>
                                                    <tr>
                                                        <th colspan="2" align="center" valign="middle" >Accidents</th>
                                                        <th colspan="6" align="center" valign="middle">Dangerous Occurrenccs</th>
                                                        
                                                      
                                                    </tr>

                                                    <tr>
                                                        <th  align="center" valign="middle" >Fatal</th>
                                                        <th  align="center" valign="middle">Serious</th>
                                                        <th  align="center" valign="middle" >Explosion</th>
                                                        <th  align="center" valign="middle">Fire</th>
                                                        <th  align="center" valign="middle" >Gassing</th>
                                                        <th  align="center" valign="middle">Toxic<br> release</th>
                                                        <th  align="center" valign="middle" >Collapse</th>
                                                        <th  align="center" valign="middle">Others</th>
                                                        
                                                        
                                                      
                                                    </tr></thead>';
                                                    $step2_select_query = db_select('labour_factory_statcell_annual_report_t2_a', 'a');
       
                                                    $step2_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
        
                  $step2_select_query->fields('a',array('ado_no_of_accidents_fatal','ado_no_of_accidents_serious','ado_no_danger_occur_explosion','ado_no_danger_occur_fire','ado_no_danger_occur_gassing','ado_no_danger_occur_toxic_release','ado_no_danger_occur_collapse','ado_no_danger_occur_others','ado_no_visit_paid_fatal_accidents','ado_no_visit_paid_serious_accidents','ado_no_visit_paid_explosion','ado_no_visit_paid_fire','ado_no_visit_paid_gassing','ado_no_visit_paid_toxic_release','ado_no_visit_paid_collapse','ado_no_visit_paid_others'));
                                                   $step2_select_query_result = $step2_select_query->execute(); 
        
                                                   $result_step2=$step2_select_query_result->fetchAssoc();
                                                   $ado_no_of_accidents_fatal=$result_step2['ado_no_of_accidents_fatal'];
                                                    $content .= '<tr>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_of_accidents_fatal'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_of_accidents_serious'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_danger_occur_explosion'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_danger_occur_fire'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_danger_occur_gassing'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_danger_occur_toxic_release'].'</td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_danger_occur_collapse'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_danger_occur_others'].'</td>
                                                    </tr>
                                                    <tr>
                                                        <th colspan="7" align="center" valign="middle" >No. of visits paid in connection with</th>
                                                        <th  align="center" valign="middle">Others</th>
                                                        
                                                      
                                                    </tr>

                                                    <tr>
                                                        <th  align="center" valign="middle" >Fatal</th>
                                                        <th  align="center" valign="middle">Serious</th>
                                                        <th  align="center" valign="middle" >Explosion</th>
                                                        <th  align="center" valign="middle">Fire</th>
                                                        <th  align="center" valign="middle" >Gassing</th>
                                                        <th  align="center" valign="middle">Toxic<br> release</th>
                                                        <th  align="center" valign="middle" >Collapse</th>
                                                        <th  align="center" valign="middle">(accident to machinery or plant etc.)</th>
                                                        
                                                        
                                                      
                                                    </tr>
                                                    <tr>
                                                        <td   align="center" valign="middle"> '.$result_step2['ado_no_visit_paid_fatal_accidents'].' </td>
                                                        <td   align="center" valign="middle"> '.$result_step2['ado_no_visit_paid_serious_accidents'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_visit_paid_explosion'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_visit_paid_fire'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_visit_paid_gassing'].' </td>
                                                        <td   align="center" valign="middle">'.$result_step2['ado_no_visit_paid_toxic_release'].'</td>
                                                        <td   align="center" valign="middle"> '.$result_step2['ado_no_visit_paid_collapse'].'</td>
                                                        <td   align="center" valign="middle"> '.$result_step2['ado_no_visit_paid_others'].'</td>
                                                    </tr>

                                                </table></div>
                                                <div class="table-panel-header"><b>2(B) Details of Accidents(Fatal/Serious) </b></div>

                                             <div class="table-responsive">
  												<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                  <thead>
                                              <tr > <th align="center" valign="middle" >Fatal / Serious</th>
      
                                              <th align="center" valign="middle" > Name Of Factory(R/UR)</th>
                                              <th  align="center" valign="middle">Address of the factories(R/UR)</th>
       
                                               <th align="center" valign="middle" >Name of injured/deceased persons</th>

                                               <th align="center" valign="middle">Date of Occurrence</th>
       
                                               <th align="center" valign="middle">Date of Expiry</th>
                                               <th align="center" valign="middle">Infringement Section/Rule Violated</th>
       
                                              <th align="center" valign="middle">Classification</th>
                                              <th align="center" valign="middle" >Legal Action Taken(Case No.)</th>
                                              <th align="center" valign="middle">Remarks</th>
                                              
                                               </tr></thead>';
                                             $query_tab_2_b=db_query('select  *  from labour_factory_statcell_annual_report_t2_b a , labour_factory_accident_classification_mst b  where CAST(a.classification_code AS INTEGER)=b.accident_classification_id  and  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));

                                               foreach($query_tab_2_b as $squan) {
                                                $i++;
                                                $row_id = $squan->row_id; 
                                                $annual_inspection_id = $squan->annual_inspection_id; 
                                                 $accident_type=$squan->accident_type;
                                                $acc_det_name_of_factory=$squan->acc_det_name_of_factory;
                                                $acc_det_address_of_factory=$squan->acc_det_address_of_factory;
                                                $acc_det_name_of_deceased_injured=$squan->acc_det_name_of_deceased_injured;

              
                                                 $acc_det_section_violation=$squan->acc_det_section_violation;
                                                 $classification_details=$squan->classification_details;
                                                  $acc_det_action_case_no=$squan->acc_det_action_case_no;
                                                   $remarks=$squan->remarks;

                                                $ade=  !trim($squan->acc_det_expiry) ? ' ' : date('d-m-Y', strtotime($squan->acc_det_expiry));


                                              $content .= ' <tr>      
                                         <td align="center" valign="middle">'.$accident_type.'</td>
                                         <td align="center" valign="middle">'.$acc_det_name_of_factory.'</td>
                                         <td align="center" valign="middle">'.$acc_det_address_of_factory.'</td>
                                         <td align="center" valign="middle">'.$acc_det_name_of_deceased_injured.'</td>
                                         <td align="center" valign="middle">'.date('d-m-Y', strtotime($squan->acc_det_date_of_accident)).'</td>
                                         <td align="center" valign="middle">'.$ade.'</td>
             
                                         <td align="center" valign="middle">'.$acc_det_section_violation.'</td>
                                         <td align="center" valign="middle">'.$classification_details.'</td>
                                         <td align="center" valign="middle">'.$acc_det_action_case_no.'</td>
                
                                         <td align="center" valign="middle" >'.$remarks.'</td>
                                         
            
              
                                       </tr>';
                                          }

                                        $content .= '   </table></div>
                                         <div class="table-panel-header"><b> 2(C) Details of Dangerous Occurrences </b></div>

                                          <table   class="table table-striped table-bordered table-responsive admin-custom-table">
										  <thead>
                                              <tr> 
                                             
      
                                              <th align="center" valign="middle" > Name Of Factory(R/UR)</th>
                                              <th  align="center" valign="middle">Address of the Factory</th>
       
                                               <th align="center" valign="middle" >Date and hour of occurrence</th>

                                               <th align="center" valign="middle">Description of the incident</th>
       
                                               <th align="center" valign="middle">No. of persons involved</th>
                                               <th align="center" valign="middle">Legal Action taken (with case no.)</th>
       
                                              <th align="center" valign="middle">Remarks</th>
                                              
                                              
                                               
                                                 </tr></thead>';

                                             $query_tab_2_c=db_query('select  *  from labour_factory_statcell_annual_report_t2_c where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));

                                          foreach($query_tab_2_c as $squan) {
                                            $i++;
                                            $row_id = $squan->row_id; 
                                            $annual_inspection_id = $squan->annual_inspection_id; 
                                            $factory_name=$squan->factory_name;
                                            $factory_address=$squan->factory_address;
                                            $date_time=$squan->date_time;
                                            $dho= !trim($date_time) ? ' ' : date('d-m-Y', strtotime($date_time));
                                            $desc_incident=$squan->desc_incident;

              
                                           $no_person=$squan->no_person;
                                           $legal_action=$squan->legal_action;
                                           $remarks=$squan->remarks;

                                             $content .= ' <tr>     
                                              <td align="center" valign="middle">'.$factory_name.'</td>
                                              <td align="center" valign="middle">'.$factory_address.'</td>
                
                                             <td align="center" valign="middle">'.$dho.'</td>
               
             
                                           <td align="center" valign="middle">'.$desc_incident.'</td>
                                           <td align="center" valign="middle">'.$no_person.'</td>
                                           <td align="center" valign="middle">'.$legal_action.'</td>
                
                                           <td align="center" valign="middle">'.$remarks.'</td>
            
                                          
              
                                          </tr>';
                                           }

                                           $content .= ' </table>

                                          <div class="table-panel-header"><b> 2(D) Number of cases of poisoning and diseases </b></div>


                                          <div class="table-responsive">
  												<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                  <thead>
                                             
      
                                              <th align="center" valign="middle" > Name of the Factory (R/UR)</th>
                                              <th  align="center" valign="middle">Address of the Factory</th>
       
                                            <th align="center" valign="middle" colspan="10" >No. of Cases</th>

                                               
                                              
                                              
                                               
                                            </tr></thead>';


                                             $step2_tab2_d_query = db_select('labour_factory_statcell_annual_report_t2_d', 'd');
       
                                             $step2_tab2_d_query->condition('d.annual_inspection_id',trim($filenumber),'=');
      
        
                  $step2_tab2_d_query->fields('d',array('factory_name' , 'factory_address' , 'lead_poisoning_no', 'lead_tetraethyl_poisoning_no' , 'phosphorus_poisoning_no' , 'mercury_poisoning_no' , 'manganese_poisoning_no' , 'arsenic_poisoning_no' , 'nitrous_fumes_no' , 'carbon_biusulphide_poisoning_no', 'benzene_poisoning_no' , 'chrome_ulceration_no' ,

    'anthrax', 'silicosis', 'halogens_derivatives_poisoning_no' , 'pathological_manifestation_no', 'epitheliomatous_cancer_no', 'toxic_anemia_no', 'toxic_jaundice_no', 'oil_cancer_no' , 'byssinosis_no', 'asbestosis_no'  ,


     'contact_dermatitis_no', 'hearing_loss_no', 'beryllium_poisoning_no' , 'co_poisoning_no' , 'pneumoconiosis_no', 'phosgene_poisoning_no' , 'occupational_cancer_no', 'isocyanates_poisoning_no' , 'toxic_nephritis_no', 'total'));
                                                   $step2_tab2_d_query_result = $step2_tab2_d_query->execute(); 
        
                                                   $result_step2_tab2_d=$step2_tab2_d_query_result->fetchAssoc();
                                                  // $factory_name=$result_step2_tab2_d['factory_name'];

                                             $content .= ' <tr>   
                                              <td align="center" valign="middle" rowspan="6">'.$result_step2_tab2_d['factory_name'].'</td>
                                              <td align="center" valign="middle" rowspan="6">'.$result_step2_tab2_d['factory_address'].'</td> 
											  <thead>
                                              <th align="center" valign="middle"  >Lead Poisoning</th> 
                                              <th align="center" valign="middle"  >Lead Thetraethyl Poisoning</th> 
                                              <th align="center" valign="middle"  >Phosphorous Poisoning</th> 
                                              <th align="center" valign="middle"  >Mercury Poisoning</th> 
                                              <th align="center" valign="middle"  >Manganese Poisoning</th> 
                                              <th align="center" valign="middle"  >Arsenic Poisoning</th> 
                                              <th align="center" valign="middle"  >Poisoning by Nitrous Fumes</th> 
                                              <th align="center" valign="middle"  >Carbon Biusulphide Poisoning</th> 
                                              <th align="center" valign="middle"  >Benzene Poisoning</th> 
                                              <th align="center" valign="middle"  >Chrome Ulceration</th> 

                                              </tr></thead>

                                              <tr>   
                                              
                                              <td align="center" valign="center"  >'.$result_step2_tab2_d['lead_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['lead_tetraethyl_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['phosphorus_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['mercury_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['manganese_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['arsenic_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['nitrous_fumes_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['carbon_biusulphide_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['benzene_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['chrome_ulceration_no'].'</td> 

                                              </tr>
                                              <tr>   
                                              <thead>
                                              <th align="center" valign="middle"  >Anthrax</th> 
                                              <th align="center" valign="middle"  >Silicosis</th> 
                                              <th align="center" valign="middle"  >Poisoning by Halogens or their derivatives</th> 
                                              <th align="center" valign="middle"  >Pathological manifestation due to radioactive substances or X-Rays</th> 
                                              <th align="center" valign="middle"  >Primary Epitheliomatous cancer of skin</th> 
                                              <th align="center" valign="middle"  >Toxic Anemia</th> 
                                              <th align="center" valign="middle"  >Toxic Jaundice</th> 
                                              <th align="center" valign="middle"  >Oil Cancer of dermatitis</th> 
                                              <th align="center" valign="middle"  >Byssinosis</th> 
                                              <th align="center" valign="middle"  >Asbestosis</th> 

                                              </tr></thead>
                                               <tr>   
                                              
                                              <td align="center" valign="center"  >'.$result_step2_tab2_d['anthrax'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['silicosis'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['halogens_derivatives_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['pathological_manifestation_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['epitheliomatous_cancer_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['toxic_anemia_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['toxic_jaundice_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['oil_cancer_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['byssinosis_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['asbestosis_no'].'</td> 

                                              </tr>
												
												<thead>
                                               <tr>   
                                              
                                              <th align="center" valign="middle"  >Occupational or contact dermatitis</th> 
                                              <th align="center" valign="middle"  >Noise induced hearing loss</th> 
                                              <th align="center" valign="middle"  >Berylium Poisoning</th> 
                                              <th align="center" valign="middle"  >Carbon Monoxide Poisoning</th> 
                                              <th align="center" valign="middle"  >Coal miners pneumoconiosis</th> 
                                              <th align="center" valign="middle"  >Phosgene Poisoning</th> 
                                              <th align="center" valign="middle"  >Occupational Cancer</th> 
                                              <th align="center" valign="middle"  >Isocyanates Poisoning</th> 
                                              <th align="center" valign="middle"  >Toxic nephritis</th> 
                                              <th align="center" valign="middle"  >Total</th> 

                                              </tr></thead>
                                              <tr>   
                                              
                                              <td align="center" valign="center"  >'.$result_step2_tab2_d['contact_dermatitis_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['hearing_loss_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['beryllium_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['co_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['pneumoconiosis_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['phosgene_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['occupational_cancer_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['isocyanates_poisoning_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['toxic_nephritis_no'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step2_tab2_d['total'].'</td> 

                                              </tr>
                                             </table></div>
                                          
                                              <div class="table-panel-header"><b> 3. Chemical Factory </b></div>
                                               <div class="table-responsive">
  												<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                  <thead>
                                             
      
                                            
                                             <th align="center" valign="middle" >SL.NO</th>
      
                                             <th align="center" valign="middle"> Name of the Factory</th>
                                             <th align="center" valign="middle">Address of the Factory</th>
       
                                             <th align="center" valign="middle">Products Manufactured</th>

                                              <th align="center" valign="middle">Raw Material used</th>
       
                                              <th align="center" valign="middle">Intermediaries by products formed</th>
                                              <th align="center" valign="middle">Finished Product</th>
       
                                             <th align="center" valign="middle">Type of hazard</th>
                                             <th align="center" valign="middle">Action</th>
                                             <th align="center" valign="middle">Maximum storage of hazardous substances</th>
        
                                             </tr></thead>';

                                              $query_tab_3=db_query('select  *  from labour_factory_statcell_annual_report_t3 where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
                                             $i=0;
                                             foreach($query_tab_3 as $squan) {
                                             $i++;
                                            $row_id = $squan->row_id; 
                                            $annual_inspection_id = $squan->annual_inspection_id; 
                                            $factory_name=$squan->factory_name;
                                            $factory_address=$squan->factory_address;
                                            $products=$squan->products;
                                            $raw_material=$squan->raw_material;

                                            $intermediaries_products=$squan->intermediaries_products;

                                            $finished_product=$squan->finished_product;
                                            $hazard_type=$squan->hazard_type;
                                            $action=$squan->action;
                                            $maximum_storage=$squan->maximum_storage;
                                        
                                            $content .= ' <tr>   
                                            <td align="center" valign="middle">'.$i.'</td> 
                                            <td align="center" valign="middle">'.$factory_name.'</td>
                                            <td align="center" valign="middle">'.$factory_address.'</td>
                                            <td align="center" valign="middle">'.$products.'</td>
                                            <td align="center" valign="middle">'.$raw_material.'</td>
                                            <td align="center" valign="middle">'.$intermediaries_products.'</td>
                                            <td align="center" valign="middle">'.$finished_product.'</td>
                                            <td align="center" valign="middle">'.$hazard_type.'</td>
                                            <td align="center" valign="middle">'.$action.'</td>
                                            <td align="center" valign="middle">'.$maximum_storage.'</td>
            
                                          
            
              
                                           </tr>';
              }


                                               
                                              
                                            $content .= ' </table> </div>

                                            <div class="table-panel-header"><b> 4. Details of order issued under various provisions of the Acts and Rules. </b></div>
                                              <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
											<thead>
                                              <tr> 
                                             
      
                                            
                                             <th align="center" valign="middle" >SL.NO</th>
      
                                             <th align="center" valign="middle"> Name</th>
                                             <th align="center" valign="middle">Address</th>
       
                                             <th align="center" valign="middle">Act and Section/Rule under which the order was issued</th>

                                              <th align="center" valign="middle">Time allowed</th>
       
                                              <th align="center" valign="middle">Brief description including result</th>
                                              
        
                                             </tr></thead>';

                                             $query_tab_4=db_query('select  *  from labour_factory_statcell_annual_report_t4 where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));

                                             $i=0;
                                             foreach($query_tab_4 as $squan) {
                                             $i++;
                                             $row_id = $squan->row_id; 
                                             $annual_inspection_id = $squan->annual_inspection_id; 
                                             $factory_name=$squan->factory_name;
                                             $factory_address=$squan->factory_address;
                                             $section_rule_issued=$squan->section_rule_issued;
                                             $time_allowed=$squan->time_allowed;
                                             $brief_description=$squan->brief_description;
                                            
                                             $content .= ' <tr>      
                                            <td align="center" valign="middle">'.$i.'</td>
                                            <td align="center" valign="middle">'.$factory_name.'</td>
                                            <td align="center" valign="middle">'.$factory_address.'</td>
                                            <td align="center" valign="middle">'.$section_rule_issued.'</td>
                                            <td align="center" valign="middle">'.$time_allowed.'</td>
                                            <td align="center" valign="middle">'.$brief_description.'</td>
                                          
                                             </tr>';
              
                                               
                                           }
                                           $content .= ' </table> </div>


                                          <div class="table-panel-header"><b> 5.A. Welfare facilities </b></div>

                                           <div class="table-responsive">
  												<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                  <thead>
                                              <tr> 
                                             
      
                                            
                                             <th align="center" valign="middle" colspan="4" >No. of factories providing</th>
      
                                             <th align="center" valign="middle" colspan="4"> No. of factories not providing</th>
                                             <th align="center" valign="middle" colspan="3">No. of factories providing for the first time during the year</th>
       
                                             
                                              
        
                                             </tr>

                                             <tr> 
                                             
      
                                            
                                             <th align="center" valign="middle"  >Ambulance Room</th>
      
                                             <th align="center" valign="middle" > Canteen</th>
                                             <th align="center" valign="middle" >Rest Room/Shelter/Lunch Room</th>
                                             <th align="center" valign="middle" > Creche</th>


                                             <th align="center" valign="middle"  >Ambulance Room</th>
                                             <th align="center" valign="middle" > Canteen</th>
                                             <th align="center" valign="middle" >Rest Room/Shelter/Lunch Room</th>
                                             <th align="center" valign="middle" > Creche</th>
                                             


                                             <th align="center" valign="middle"  >Ambulance Room/Creche</th>
      
                                             <th align="center" valign="middle" > Canteen</th>
                                             <th align="center" valign="middle" >Rest Room/Shelter/Lunch Room</th>
                                             
                                           </tr></thead>';
                                             
                                              
        
                                             


                                            $step6_select_query_a = db_select('labour_factory_statcell_annual_report_t5_a', 'a');
       
                                            $step6_select_query_a->condition('a.annual_inspection_id',trim($filenumber),'=');
      
        
                                $step6_select_query_a->fields('a',array('factory_providing_ambulance','factory_providing_canteen','factory_providing_creche','factory_not_providing_ambulance','factory_not_providing_canteen','factory_not_providing_creche','factory_providing_1st_canteen','factory_providing_rest_shelter_lunch', 'factory_not_providing_rest_shelter_lunch','factory_providing_1st_rest_shelter_lunch','factory_providing_1st_ambulance_creche'));
                                           $step6_select_query_a_result = $step6_select_query_a->execute(); 
        
                                           $result_step6_A=$step6_select_query_a_result->fetchAssoc();
                                           $factory_providing_ambulance=$result_step6_A['factory_providing_ambulance'];

                                             $content .= ' <tr>   
                                              
                                              <td align="center" valign="center"  >'.$result_step6_A['factory_providing_ambulance'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_providing_canteen'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_providing_creche'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_providing_rest_shelter_lunch'].'</td> 

                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_not_providing_ambulance'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_not_providing_canteen'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_not_providing_creche'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_not_providing_rest_shelter_lunch'].'</td>

                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_providing_1st_ambulance_creche'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_providing_1st_canteen'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_step6_A['factory_providing_1st_rest_shelter_lunch'].'</td> 

                                              </tr>
                                             </table></div> 

                                            <div class="table-panel-header"><b> 5.B. Additional health and Welfare facilities </b></div>

                                           <div class="table-responsive">
  												<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                                  <thead>
                                            <tr> 
                                             <th align="center" valign="middle" rowspan="2"  >Ambulance</th>
      
                                             <th align="center" valign="middle" colspan="3"> Qualified Medical Practitioners</th>
                                             <th align="center" valign="middle" rowspan="2">Industrial hygiene laboratory</th>
                                             <th align="center" valign="middle" rowspan="2">Industrial laboratory</th>
                                             <th align="center" valign="middle" rowspan="2">Industrial health supervisor</th>
                                             </tr>
                                             
                                              <tr> 
                                             <th align="center" valign="middle"   >Whole time</th>
      
                                             <th align="center" valign="middle" > Part time</th>
                                             <th align="center" valign="middle" >Consultant (Specialist)</th>
                                             
                                             </tr></thead>';

                                             $step5_select_B_query = db_select('labour_factory_statcell_annual_report_t5_b', 'b');
       
                                             $step5_select_B_query->condition('b.annual_inspection_id',trim($filenumber),'=');
        
                                            $step5_select_B_query->fields('b',array('ambulance' ,'whole_time' ,'part_time' ,
                                            'consultant' ,
                                            'hygiene_lab' ,
                                            'hygienist' ,
                                           'health_supervisor' ,
                                           'blood_examined' ,
                                           'urine_examined' ,
                                           'stool_examined' ,
                                           'radiology_xray' ,
                                           'lung_function_examined' ,
                                           'sputum_examined' ,
                                           'liver_function_examined' ,
                                            'audiometry_examined' ,
                                            'occupational_examined' ,
                                            'fitness_examined' ,
                                            'others_examined'));
                                            $step5_result_B = $step5_select_B_query->execute(); 
        
                                            $result_5B=$step5_result_B->fetchAssoc();
                                            $ambulance=$result_5B['ambulance'];




                                         


                                           $content .= ' <tr>   
                                              
                                              <td align="center" valign="center"  >'.$result_5B['ambulance'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_5B['whole_time'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_5B['part_time'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_5B['consultant'].'</td> 

                                              <td align="center" valign="middle"  >'.$result_5B['hygiene_lab'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_5B['hygienist'].'</td> 
                                              <td align="center" valign="middle"  >'.$result_5B['health_supervisor'].'</td> 
                                              

                                              </tr>

                                    
                                         </table> </div>
                                        <div class="table-panel-header"><b> 5.C Clinical and laboratory examinations of workers during the year </b></div>
                                         <div class="table-responsive">
  										<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                         <thead>
                                            <tr> 
                                             <th align="center" valign="middle"   >Nature of Laboratory examinations</th>
      
                                             <th align="center" valign="middle" > No. of workers examined</th>
                                             
                                             </tr>

                                             <tr> 
                                             <th align="left"  colspan="2"   >1.Pathological</th>
                                            </tr></thead>
                                            
                                             <tr> 
                                             <td align="left" valign="middle"   >(i) Blood</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['blood_examined'].' </td>
                                             
                                             </tr>
                                             
                                             <tr> 
                                             <td align="left" valign="middle"   >(ii) Urine</td>
      
                                             <td align="center" valign="middle" > '.$result_5B['urine_examined'].'</td>
                                             
                                             </tr>
                                             <tr> 
                                             <td align="left" valign="middle"   >(iii) Stool -</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['stool_examined'].' </td>
                                             
                                             </tr>

                                              <tr> 
                                             <td align="left" valign="middle"   >2. Radiological (X-Ray) -</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['radiology_xray'].' </td>
                                             
                                             </tr>

                                             <tr> 
                                             <td align="left" valign="middle" colspan="2"   >3. Physiological :</td>
      
                                           
                                             
                                             </tr>

                                              <tr> 
                                             <td align="left" valign="middle"   >(i) Lung Function test -</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['lung_function_examined'].' </td>
                                             
                                             </tr>

                                              <tr> 
                                             <td align="left" valign="middle"   >(ii) Sputum test -</td>
      
                                             <td align="center" valign="middle" > '.$result_5B['sputum_examined'].'</td>
                                             
                                             </tr>

                                              <tr> 
                                             <td align="left" valign="middle"   >(iii) Liver function test -</td>
      
                                             <td align="center" valign="middle" > '.$result_5B['liver_function_examined'].'</td>
                                             
                                             </tr>

                                             <tr> 
                                             <td align="left" valign="middle"   >(iv) Audiometry -</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['audiometry_examined'].' </td>
                                             
                                             </tr>

                                              <tr> 
                                             <td align="left" valign="middle"   >(v) Occupational diseases suspected -</td>
      
                                             <td align="center" valign="middle" > '.$result_5B['occupational_examined'].'</td>
                                             
                                             </tr>

                                             <tr> 
                                             <td align="left" valign="middle"   >(vi) No. of workers declared unfit for further work -</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['fitness_examined'].' </td>
                                             
                                             </tr>

                                             <tr> 
                                             <td align="left" valign="middle"   >(vii)Others -</td>
      
                                             <td align="center" valign="middle" >'.$result_5B['others_examined'].' </td>
                                             
                                             </tr>

                                          </table></div> 
                                          <div class="table-panel-header"><b> 6.A. Welfare Officer and Safety Officer </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                              <thead>
                                            <tr> 
                                             <th align="center" valign="middle" rowspan="2"   >Name of the Factory</th>
      
                                             <th align="center" valign="middle" colspan="2" > Number required to be appointed under the statute</th>
                                             <th align="center" valign="middle" colspan="2" > Actually appointed</th>
                                             
                                             </tr>

                                             <tr> 
                                             <th align="center" valign="middle"    >Welfare Officer</th>
      
                                             <th align="center" valign="middle"  > Safety Officer</th>
                                             <th align="center" valign="middle"  > Welfare Officer</th>
                                             <th align="center" valign="middle"  > Safety Officer</th>
                                             
                                             </tr></thead>';
                                           $query_tab_6_a=db_query('select  *  from labour_factory_statcell_annual_report_t6_a where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));
                                           foreach($query_tab_6_a as $squan) {
                                           $i++;
                                          $row_id = $squan->row_id; 
                                          $annual_inspection_id = $squan->annual_inspection_id; 
                                          $factory_name=$squan->factory_name; 
                                          $welfare_officer_required=$squan->welfare_officer_required;     
                                          $safety_officer_required=$squan->safety_officer_required;   
                                          $welfare_officer_appointed=$squan->welfare_officer_appointed; 
                                          $safety_officer_appointed=$squan->safety_officer_appointed;  

                                              $content .= ' <tr>   
                                              <tr> 
                                             <td align="left" valign="middle"   >'.$factory_name.'</td>
      
                                             <td align="center" valign="middle" >'.$welfare_officer_required.' </td>

                                            <td align="left" valign="middle"   >'.$safety_officer_required.'</td>
                                            <td align="left" valign="middle"   >'.$welfare_officer_appointed.'</td>
                                            <td align="left" valign="middle"   >'.$safety_officer_appointed.'</td>
                                             
                                             </tr>';

                                         }
                                         $content .= ' </table></div>
                                        <div class="table-panel-header"><b> 6(B) Details of Safety policy and safety committee </b></div>
                                           <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                             <thead>
                                            <tr> 
                                             <th align="center" valign="middle"    >Name of the factory<br> having safety committees.</th>
      
                                             <th align="center" valign="middle"  > Address of <br>the factory</th>
                                             <th align="center" valign="middle"  > How the Committee <br>has been set up?( By nomination/election).</th>
                                             
                                          

                                           
                                             <th align="center" valign="middle"    >Whether any Safety <br>policy has been framed by the factory <br>with respect to health <br>and safety of the workers</th>
      
                                             <th align="center" valign="middle"  > if, so has it been submitted <br>to chief inspector of factories,<br> West Bengal?</th>
                                             
                                             </tr></thead>';

                                           $query_tab_6_b=db_query('select  *  from labour_factory_statcell_annual_report_t6_b where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));

                                           foreach($query_tab_6_b as $squan) {
                                            $i++;
                                            $row_id = $squan->row_id; 
                                            $annual_inspection_id = $squan->annual_inspection_id; 
                                            $factory_name=$squan->factory_name; 
                                            $factory_address=$squan->factory_address;     
                                            $committee_setup=$squan->committee_setup;   
                                            $safety_policy=$squan->safety_policy; 
                                            $is_submitted_to_cif=$squan->is_submitted_to_cif; 

                                             $content .= ' <tr>   
                                              <tr> 
                                             <td align="left" valign="middle"   >'.$factory_name.'</td>
      
                                             <td align="center" valign="middle" >'.$factory_address.' </td>

                                            <td align="left" valign="middle"   >'.$committee_setup.'</td>
                                            <td align="left" valign="middle"   >'.$safety_policy.'</td>
                                            <td align="left" valign="middle"   >'.$is_submitted_to_cif.'</td>
                                             
                                             </tr>';
                                         }

                                           $content .= ' </table></div>

                                          <div class="table-panel-header"><b> 7.A. No. of Factories where violations were observed in respect of </b></div>
                                         <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                             <thead>
                                            <tr> 
                                            <th align="center" valign="middle"  >Regn. Licence etc.</th>
                                            <th align="center" valign="middle"  > Plan</th>
                                            <th align="center" valign="middle"  > Ventilation & temperature</th>
                                            <th align="center" valign="middle"  > Dust & Fume</th>
                                            <th align="center" valign="middle"  > Ovr Cowding</th>
                                            <th align="center" valign="middle"  > Lighting</th>
                                            <th align="center" valign="middle"  > Drinking Water</th>
                                            <th align="center" valign="middle"  > Latrine & Urinal</th>
                                            </tr>

                                            <tr> 
                                            <th align="center" valign="middle"  > S/6</th>
                                            <th align="center" valign="middle"  > R/3</th>
                                            <th align="center" valign="middle"  > S/13</th>
                                            <th align="center" valign="middle"  > S/14</th>
                                            <th align="center" valign="middle"  > S/16</th>
                                            <th align="center" valign="middle"  > S/17</th>
                                            <th align="center" valign="middle"  > S/18</th>
                                            <th align="center" valign="middle"  > S/19</th>
                                            </tr></thead>
                                              ';
                                             $step7_taba_query = db_select('labour_factory_statcell_annual_report_t7_a', 'a');
       
                                             $step7_taba_query->condition('a.annual_inspection_id',trim($filenumber),'=');
                                             $step7_taba_query->fields('a',array( 's_6' ,'r_3' ,'s_13' ,'s_14' ,'s_16' , 's_17' , 's_18' ,'s_19' ,  's_21' ,'s_22' ,
  's_23' ,
  's_24' ,
  's_28' ,
  's_29' ,
  's_30' ,
  's_31' ,
  's_32' ,
  's_33' ,
  's_34' ,
  's_35' ,
  's_36' ,
  's_37' ,
  's_38' ,
  's_42 ',
  'r_65' ,
  'r_66',
  's_46' ,
  's_47' ,
  's_48' ,
  's_51' ,
  's_52' ,
  's_54' ,
  's_55' ,
  's_56' ,
  's_57' ,
  's_58' ,
  's_59' ,
  's_60' ,
  's_61' ,
  's_62',
  's_64' ,
  's_66' ,
  's_67_to_s_73' ,
  's_79' ,
  'r_88' ,
  'r_89' ,
  's_80'));
   $step7_a_query_result = $step7_taba_query->execute(); 
        
        $result_step7a=$step7_a_query_result->fetchAssoc();
        
        
                                          $content .= '<tr> 
                                             <td align="center" valign="middle"   >'.$result_step7a['s_6'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7a['r_3'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7a['s_13'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_14'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_16'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7a['s_17'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7a['s_18'].'</td>
                                             
                                             <td align="center" valign="middle"   >'.$result_step7a['s_19'].'</td>
                                             
                                             </tr>
											
											<thead>
                                             <tr> 
                                            <th align="center" valign="middle"  >Fencing of machinery</th>
                                            <th align="center" valign="middle"  > Work on machinery in motion</th>
                                            <th align="center" valign="middle"  > Employment of young persons on dangerous machine</th>
                                            <th align="center" valign="middle"  > Striking gear etc.</th>
                                            <th align="center" valign="middle"  > Hoists & lifts</th>
                                            <th align="center" valign="middle"  > Lifting machinery</th>
                                            <th align="center" valign="middle"  > Revolving machinery</th>
                                            <th align="center" valign="middle"  > Pressure plant</th>
                                            </tr>

                                            <tr> 
                                            <th align="center" valign="middle"  > S/21</th>
                                            <th align="center" valign="middle"  > S/22</th>
                                            <th align="center" valign="middle"  > S/23</th>
                                            <th align="center" valign="middle"  > S/24</th>
                                            <th align="center" valign="middle"  > S/28</th>
                                            <th align="center" valign="middle"  > S/29</th>
                                            <th align="center" valign="middle"  > S/30</th>
                                            <th align="center" valign="middle"  > S/31</th>
                                            </tr></thead>

                                            <tr> 
                                             <td align="center" valign="middle"   >'.$result_step7a['s_21'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7a['s_22'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7a['s_23'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_24'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_28'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7a['s_29'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7a['s_30'].'</td>
                                             
                                             <td align="center" valign="middle"   >'.$result_step7a['s_31'].'</td>
                                             
                                             </tr>
											
											<thead>
                                           <tr> 
                                            <th align="center" valign="middle"  > Floors stairs, etc.</th>
                                            <th align="center" valign="middle"  > Pits sumps, etc.</th>
                                            <th align="center" valign="middle"  > excessive wt.</th>
                                            <th align="center" valign="middle"  > Protection of eyes.</th>
                                            <th align="center" valign="middle"  > Dangerous fumes</th>
                                            <th align="center" valign="middle"  > Explosive of inflammable dust etc</th>
                                            <th align="center" valign="middle"  > Precaution in case of fire</th>
                                            <th align="center" valign="middle"  > Washing facilities</th>
                                            </tr>

                                            <tr> 
                                            <th align="center" valign="middle"  > S/32</th>
                                            <th align="center" valign="middle"  > S/33</th>
                                            <th align="center" valign="middle"  > S/34</th>
                                            <th align="center" valign="middle"  > S/35</th>
                                            <th align="center" valign="middle"  > S/36</th>
                                            <th align="center" valign="middle"  > S/37</th>
                                            <th align="center" valign="middle"  > S/38</th>
                                            <th align="center" valign="middle"  > S/42</th>
                                            </tr>
											</thead>
											
                                            <tr> 
                                             <td align="center" valign="middle"   >'.$result_step7a['s_32'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7a['s_33'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7a['s_34'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_35'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_36'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7a['s_37'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7a['s_38'].'</td>
                                             
                                             <td align="center" valign="middle"   >'.$result_step7a['s_42'].'</td>
                                             
                                             </tr>
											
											
											<thead>
                                             <tr> 
                                            <th align="center" valign="middle"  > First aid</th>
                                            <th align="center" valign="middle"  > Ambulance room</th>
                                            <th align="center" valign="middle"  > Canteen.</th>
                                            <th align="center" valign="middle"  > Sheer, rest room Lunch room.</th>
                                            <th align="center" valign="middle"  > Creche</th>
                                            <th align="center" valign="middle"  > Weekly hours</th>
                                            <th align="center" valign="middle"  > Weekly holidays</th>
                                            <th align="center" valign="middle"  > Daily hours</th>
                                            </tr>

                                            <tr> 
                                            <th align="center" valign="middle"  > R/65</th>
                                            <th align="center" valign="middle"  > R/66</th>
                                            <th align="center" valign="middle"  > S/46</th>
                                            <th align="center" valign="middle"  > S/47</th>
                                            <th align="center" valign="middle"  > S/48</th>
                                            <th align="center" valign="middle"  > S/51</th>
                                            <th align="center" valign="middle"  > S/52</th>
                                            <th align="center" valign="middle"  > S/54</th>
                                            </tr>
											</thead>
											
											
                                            <tr> 
                                             <td align="center" valign="middle"   >'.$result_step7a['r_65'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7a['r_66'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7a['s_46'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_47'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_48'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7a['s_51'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7a['s_52'].'</td>
                                             
                                             <td align="center" valign="middle"   >'.$result_step7a['s_54'].'</td>
                                             
                                             </tr>
                                         
										 <thead>
                                         <tr> 
                                            <th align="center" valign="middle"  > Rest interval</th>
                                            <th align="center" valign="middle"  > Spread over</th>
                                            <th align="center" valign="middle"  > Night Shifts.</th>
                                            <th align="center" valign="middle"  > Overlapping Shifts.</th>
                                            <th align="center" valign="middle"  > Overtime wages</th>
                                            <th align="center" valign="middle"  > Double Employment</th>
                                            <th align="center" valign="middle"  > Notice of periods of work</th>
                                            <th align="center" valign="middle"  > Register of adult workers</th>
                                            </tr>

                                            <tr> 
                                            <th align="center" valign="middle"  > S/55</th>
                                            <th align="center" valign="middle"  > S/56</th>
                                            <th align="center" valign="middle"  > S/57</th>
                                            <th align="center" valign="middle"  > S/58</th>
                                            <th align="center" valign="middle"  > S/59</th>
                                            <th align="center" valign="middle"  > S/60</th>
                                            <th align="center" valign="middle"  > S/61</th>
                                            <th align="center" valign="middle"  > S/62</th>
                                            </tr>
											</thead>
											
											
                                            <tr> 
                                             <td align="center" valign="middle"   >'.$result_step7a['s_55'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7a['s_56'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7a['s_57'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_58'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_59'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7a['s_60'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7a['s_61'].'</td>
                                             
                                             <td align="center" valign="middle"   >'.$result_step7a['s_62'].'</td>
                                             
                                             </tr>

											<thead>
                                            <tr> 
                                            <th align="center" valign="middle"  > Exemption Rules</th>
                                            <th align="center" valign="middle"  > Employment of Women</th>
                                            <th align="center" valign="middle"  > Employment of Young persons.</th>
                                            <th align="center" valign="middle"  > Leave with wage.</th>
                                            <th align="center" valign="middle"  > Leave register</th>
                                            <th align="center" valign="middle"  > Leave book</th>
                                            <th align="center" valign="middle"  > Wages for Leave periods	</th>
                                            <th align="center" valign="middle"  > Register of adult workers</th>
                                            </tr>

                                            <tr> 
                                            <th align="center" valign="middle"  > S/64</th>
                                            <th align="center" valign="middle"  > S/66</th>
                                            <th align="center" valign="middle"  > S/67 to S/73</th>
                                            <th align="center" valign="middle"  > S/79</th>
                                            <th align="center" valign="middle"  > R/88</th>
                                            <th align="center" valign="middle"  > R/89</th>
                                            <th align="center" valign="middle"  > S/80</th>
                                            <th align="center" valign="middle"  > &nbsp;</th>
                                            </tr>
											</thead>
											
                                            <tr> 
                                             <td align="center" valign="middle"   >'.$result_step7a['s_64'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7a['s_66'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7a['s_67_to_s_73'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['s_79'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7a['r_88'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7a['r_89'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7a['s_80'].'</td>
                                             <td align="center" valign="middle"   >&nbsp;</td>
                                             
                                            
                                             
                                             </tr>





                                         </table></div>



                                          <div class="table-panel-header"><b> 7.B. RULE 47 </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                            <thead>
                                            <tr> 
                                            <th align="center" valign="middle"  >Sch. I</th>
                                            <th align="center" valign="middle"  > Sch. II</th>
                                            <th align="center" valign="middle"  > Sch. III</th>
                                            <th align="center" valign="middle"  > Sch. IV</th>
                                            <th align="center" valign="middle"  > Sch. V</th>
                                            <th align="center" valign="middle"  > Sch. VI</th>
                                            <th align="center" valign="middle"  > Sch. VII</th>
                                            
                                            </tr></thead>';

                                             $step7b_select_query = db_select('labour_factory_statcell_annual_report_t7_rule_47', 'b');
       
                                             $step7b_select_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
		
                                            $step7b_select_query->fields('b',array('s_i','s_ii','s_iii','s_iv','s_v','s_vi','s_vii'));
                                            $step7b_select_query_result = $step7b_select_query->execute(); 
		
		                                    $result_step7b=$step7b_select_query_result->fetchAssoc();
		                                   

                                            $content .= '<tr>   
                                             <td align="center" valign="middle"   >'.$result_step7b['s_i'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7b['s_ii'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7b['s_iii'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7b['s_iv'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7b['s_v'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7b['s_vi'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7b['s_vii'].'</td>
                                            
                                            
                                             
                                             </tr>
                                         </table></div>

                                          <div class="table-panel-header"><b> 7.C. RULE 94 </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                            <thead>
                                            <tr> 
                                            <th align="center" valign="middle"  >Sch. I</th>
                                            <th align="center" valign="middle"  > Sch. II</th>
                                            <th align="center" valign="middle"  > Sch. III</th>
                                            <th align="center" valign="middle"  > Sch. IV</th>
                                            <th align="center" valign="middle"  > Sch. V</th>
                                            <th align="center" valign="middle"  > Sch. VI</th>
                                            <th align="center" valign="middle"  > Sch. VII</th>
                                            <th align="center" valign="middle"  > Sch. VIII</th>
                                            <th align="center" valign="middle"  > Sch. IX</th>
                                            <th align="center" valign="middle"  > Sch. X</th>

                                            <th align="center" valign="middle"  > Sch. XI</th>
                                            <th align="center" valign="middle"  > Sch. XII</th>
                                            <th align="center" valign="middle"  > Sch. XIII</th>
                                            <th align="center" valign="middle"  > Sch. XIV</th>
                                             <th align="center" valign="middle"  > Sch. XV</th>
                                            <th align="center" valign="middle"  > Sch. XVI</th>
                                            </tr></thead>';
                                             $step7c_select_query = db_select('labour_factory_statcell_annual_report_t7_rule_94', 'c');
       
                                            $step7c_select_query->condition('c.annual_inspection_id',trim($filenumber),'=');
      
		
                                            $step7c_select_query->fields('c',array('s_i' ,
                                           's_ii' ,
                                           's_iii' ,
                                           's_iv' ,
                                           's_v' ,
  's_vi' ,
  's_vii' ,
  's_viii' ,
  's_ix' ,
  's_x' ,
  's_xi' ,
  's_xii' ,
  's_xiii' ,
  's_xiv' ,
  's_xv' ,
  's_xvi' ,
  's_xvii' ,
  's_xviii' ,
  's_xix' ,
  's_xx',
  's_xxi' ,
  's_xxii',
  's_xxiii' ,
  's_xxiv' ,
  's_xxv' ,
  's_xxvi',
  's_xxvii' ,
  's_xxviii' ,
  's_xxix' ,
  's_xxx' ,
  's_xxxi' ,

  's_xxxii' ));
        $step7c_result = $step7c_select_query->execute(); 
		
		$result_step7c=$step7c_result->fetchAssoc();

		                                          $content .= '<tr>   
                                             <td align="center" valign="middle"   >'.$result_step7c['s_i'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7c['s_ii'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7c['s_iii'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_iv'].'</td>

                                            
                                             <td align="center" valign="middle"   >'.$result_step7c['s_v'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_vi'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_vii'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_viii'].'</td>


                                             





      
                                            
                                            <td align="center" valign="middle" >'.$result_step7c['s_ix'].' </td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_x'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_xi'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_xii'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7c['s_xiii'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xiv'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xv'].'</td>
                                             <td align="center" valign="middle" >'.$result_step7c['s_xvi'].' </td>
                                             
      
                                             




                                            
                                            
                                             
                                             </tr>


											<thead>
                                            <tr>
                                            <th align="center" valign="middle"  > Sch. XVII</th>
                                            <th align="center" valign="middle"  > Sch. XVIII</th>
                                            <th align="center" valign="middle"  > Sch. XIX</th>
                                            <th align="center" valign="middle"  > Sch. XX</th>

                                            <th align="center" valign="middle"  > Sch. XXI</th>
                                            <th align="center" valign="middle"  > Sch. XXII</th>
                                            <th align="center" valign="middle"  > Sch. XXIII</th>
                                            <th align="center" valign="middle"  > Sch. XXIV</th>

                                            <th align="center" valign="middle"  > Sch. XXV</th>
                                            <th align="center" valign="middle"  > Sch. XXVI</th>
                                            <th align="center" valign="middle"  > Sch. XXVII</th>
                                            <th align="center" valign="middle"  > Sch. XXVIII</th>

                                            <th align="center" valign="middle"  > Sch. XXIX</th>
                                            <th align="center" valign="middle"  > Sch. XXX</th>
                                            <th align="center" valign="middle"  > Sch. XXXI</th>
                                            <th align="center" valign="middle"  > Sch. XXXII</th>
                                             
                                            
                                            </tr>
											</thead>

                                            <tr>   
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xvii'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_step7c['s_xviii'].' </td>

                                            <td align="center" valign="middle"   >'.$result_step7c['s_xix'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_xx'].'</td>


                                            
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xxi'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xxii'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xxiii'].'</td>
                                              <td align="center" valign="middle"   >'.$result_step7c['s_xxiv'].'</td>


                                            
      
                                             
                                            <td align="center" valign="middle" >'.$result_step7c['s_xxv'].' </td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_xxvi'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_xxvii'].'</td>
                                            <td align="center" valign="middle"   >'.$result_step7c['s_xxviii'].'</td>

                                             <td align="center" valign="middle"   >'.$result_step7c['s_xxix'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xxx'].'</td>
                                             <td align="center" valign="middle"   >'.$result_step7c['s_xxxi'].'</td>
                                             <td align="center" valign="middle" >'.$result_step7c['s_xxxii'].' </td>
                                             
      
                                             

                                            
                                          </tr>
                                             


                                            
                                            
                                             
                                            


                                        </table></div>




                                           <div class="table-panel-header"><b> 7.D. TAB-H </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                            <thead>
                                            <tr> 
                                            <th align="center" valign="middle"  > S-7A</th>
                                            <th align="center" valign="middle"  > R-63B</th>
                                            <th align="center" valign="middle"  > R-63C</th>
                                            <th align="center" valign="middle"  > R-63D</th>
                                            <th align="center" valign="middle"  > R-63E</th>
                                            <th align="center" valign="middle"  > R-63F</th>
                                            <th align="center" valign="middle"  > R-63G</th>
                                            <th align="center" valign="middle"  > R-63J</th>
                                            <th align="center" valign="middle"  > R-63K</th>
                                            <th align="center" valign="middle"  > R-63L</th>
                                            
                                            </tr></thead>';

                                             $step7_tabh_query = db_select('labour_factory_statcell_annual_report_t7_tab_h', 'd');
       
                                            $step7_tabh_query->condition('d.annual_inspection_id',trim($filenumber),'=');
      
		
                                           $step7_tabh_query->fields('d',array('s_7a','r_63b','r_63c','r_63d','r_63e','r_63f','r_63g','r_63j','r_63k','r_63l'));
                                            $step7_tabh_query_result = $step7_tabh_query->execute(); 
		
		                                   $result_tabh=$step7_tabh_query_result->fetchAssoc();
		                                   $s_7a=$result_tabh['s_7a'];
       
		                                   

                                            $content .= '<tr>   
                                             <td align="center" valign="middle"   >'.$result_tabh['s_7a'].'</td>
      
                                             <td align="center" valign="middle" >'.$result_tabh['r_63b'].' </td>

                                            <td align="center" valign="middle"   >'.$result_tabh['r_63c'].'</td>
                                            <td align="center" valign="middle"   >'.$result_tabh['r_63d'].'</td>
                                            <td align="center" valign="middle"   >'.$result_tabh['r_63e'].'</td>

                                             <td align="center" valign="middle"   >'.$result_tabh['r_63f'].'</td>
                                             <td align="center" valign="middle"   >'.$result_tabh['r_63g'].'</td>
                                             <td align="center" valign="middle"   >'.$result_tabh['r_63j'].'</td>
                                             <td align="center" valign="middle"   >'.$result_tabh['r_63k'].'</td>
                                             <td align="center" valign="middle"   >'.$result_tabh['r_63l'].'</td>
                                            
                                            
                                             
                                             </tr>
                                         </table></div>

                                          <div class="table-panel-header"><b> 8.Complaints </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                             <thead>
                                            <tr> 
                                            <th  valign="middle"  > &nbsp;</th>
                                            <th  valign="middle"  > Number</th>
                                            <th  valign="middle"  > Investigated</th>
                                            <th  valign="middle"  > Violation observed</th>
                                            <th  valign="middle"  > Action taken</th>
                                            <th  valign="middle"  > Remarks</th>
                                            
                                            
                                            </tr></thead>';

                                            $step8_query = db_select('labour_factory_statcell_annual_report_t8', 'b');
       
                                           $step8_query->condition('b.annual_inspection_id',trim($filenumber),'=');
      
		
        $step8_query->fields('b',array('reg_recv_no' ,'reg_investigated' ,'reg_violation' ,'reg_action' ,'reg_remarks' ,'unreg_recv_no' ,'unreg_investigated' ,'unreg_violation' , 'unreg_action','unreg_remarks'  ));
                                          $step8_result = $step8_query->execute(); 
		
		                                 $result_8=$step8_result->fetchAssoc();
		                                 $reg_recv_no=$result_8['reg_recv_no'];


                                        $content .= '  <tr>   
                                             <td  valign="middle"   >Registered factories</td>
      
                                             <td  valign="middle" >'.$result_8['reg_recv_no'].' </td>

                                            <td  valign="middle"   >'.$result_8['reg_investigated'].'</td>
                                            <td  valign="middle"   >'.$result_8['reg_violation'].'</td>
                                            <td  valign="middle"   >'.$result_8['reg_action'].'</td>
                                      
                                            <td  valign="middle"   >'.$result_8['reg_remarks'].'</td>
                                            </tr>
                                           <tr>   
                                             <td  valign="middle"   >Unregister factories</td>  

                                           <td  valign="middle"   >'.$result_8['unreg_recv_no'].'</td>

                                           <td  valign="middle"   >'.$result_8['unreg_investigated'].'</td>


                                           <td  valign="middle"   >'.$result_8['unreg_violation'].'</td>

                                           <td  valign="middle"   >'.$result_8['unreg_action'].'</td>

                                           <td  valign="middle"   >'.$result_8['unreg_remarks'].'</td>

                                         

                                       </tr></table></div>
                                             
                                            
                                            
                                            <div class="table-panel-header"><b> 9.Information relating to prosecution proceedings instituted during the year (under the Factories Act) </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                            <thead>
                                            <tr> 
                                                 <th align="center" valign="middle"  > SL.NO</th>
                                            <th align="center" valign="middle"  > Name of the factory</th>
                                            <th align="center" valign="middle"  > Address of the factory</th>
                                            <th align="center" valign="middle"  > Registered/un-registered factory</th>
                                            <th align="center" valign="middle"  > Persons against whom <br>launched(Occupier, Manager etc.)</th>
                                            <th align="center" valign="middle"  > Case Number</th>
                                            <th align="center" valign="middle"  > Name of Court</th>

                                            <th align="center" valign="middle"  > Sections/Rules <br>violated with a short description</th>

                                            <th align="center" valign="middle"  > Result</th>
                                             <th align="center" valign="middle"  >Amount of fines</th>
                                            
                                            
                                            </tr></thead>'; 
                                            

                                     $query_tab_9=db_query('select  *  from labour_factory_statcell_annual_report_t9_10 where  annual_inspection_id = :anid and is_pending  = :ispen', array(':anid' => trim($filenumber) , ':ispen' => 0 ));


                                       $i=0;
		                          foreach($query_tab_9 as $squan) {
			                       $i++;
		                          $row_id = $squan->row_id; 
		                          $annual_inspection_id = $squan->annual_inspection_id; 
	                              $factory_name=$squan->factory_name; 
			                      $factory_address=$squan->factory_address;     
			                      $reg_unreg=$squan->reg_unreg;   
                                  $person_prosecuted=$squan->person_prosecuted; 
                                  $case_number=$squan->case_number;  

            
                                  $court_name=$squan->court_name;  
                                  $violation_description=$squan->violation_description; 
                                  $results=$squan->results; 
                                  $total_fine=$squan->total_fine; 

                                 $content .= '<tr>

                                    <td align="center" valign="middle"   >'.$i.'</td>
				                   <td align="center" valign="middle"   >'.$factory_name.'</td>
			                       <td align="center" valign="middle"   >'.$factory_address.'</td>
                                   <td align="center" valign="middle"   >'.$reg_unreg.'</td>
                                   <td align="center" valign="middle"   >'.$person_prosecuted.'</td>
                                   <td align="center" valign="middle"   >'.$case_number.'</td>
                                   <td align="center" valign="middle"   >'.$court_name.'</td>
                                   <td align="center" valign="middle"   >'.$violation_description.'</td>
                                   <td align="center" valign="middle"   >'.$results.'</td>
                                   <td align="center" valign="middle"   >'.$total_fine.'</td>
                                   
			
				
			                     </tr>';
              
			   
	                             }



                              $content .= '  </table> </div>


                               <div class="table-panel-header"><b>10. Information relating to pending cases (Under the factories Act) of previous Year/Years. </b></div>
                                          <div class="table-responsive">
  											<table  class="table table-striped table-bordered table-responsive admin-custom-table" >
                                            <thead>
                                            <tr> 
                                            <th align="center" valign="middle"  > Name of the factory</th>
                                            <th align="center" valign="middle"  > Address of <br>the factory</th>
                                            <th align="center" valign="middle"  > Registered/un-registered <br>factory</th>
                                            <th align="center" valign="middle"  > Persons against <br> whom launched(Occupier, Manager etc.)</th>
                                            <th align="center" valign="middle"  > Case Number</th>
                                            <th align="center" valign="middle"  > Name of Court</th>

                                            <th align="center" valign="middle"  > Sections/Rules <br>violated with a short description</th>

                                            <th align="center" valign="middle"  > Result</th>
                                             <th align="center" valign="middle"  > Case Date </th>
                                             <th align="center" valign="middle"  >Amount of fines</th>
                                            
                                            
                                            </tr></thead>';  


                   $previous_year=$thisYear - 1;
        
        //print "ssss".$previous_year;
       // exit;
   
      if($annual_form_type=='CALENDAR'){
        $previous_from_year_dt='1900-01-01';
        $previous_to_year_dt=$previous_year.'-12-31';
    }
    elseif($annual_form_type=='FINANCIAL'){
        $previous_from_year_dt='1900-01-01';
        $previous_to_year_dt=date("Y")."-03-31";
    }                         

                                       
            $tab10_pending_case_select_query = db_select('labour_factory_statcell_annual_report_t9_10', 'a');
       
           $tab10_pending_case_select_query->InnerJoin('labour_factory_statcell_annual_report', 'b', 'a.annual_inspection_id=b.annual_inspection_id');
           $tab10_pending_case_select_query->condition('b.inspector_id',trim($inspector_id),'=');
           $tab10_pending_case_select_query->condition('a.case_date',trim($previous_from_year_dt),'>=');
           $tab10_pending_case_select_query->condition('a.case_date',trim($previous_to_year_dt),'<=');
           $tab10_pending_case_select_query->condition('a.results','PENDING','=');
           $tab10_pending_case_select_query->condition('a.is_disabled', 0 ,'=');

            $tab10_pending_case_select_query->fields('a',array('row_id','factory_name','factory_address',
        'reg_unreg','person_prosecuted','case_number','court_name','violation_description','results','total_fine','case_date'));

             $tab10_pending_case_select_query->fields('b',array('annual_inspection_id'));

            $query_tab_10 = $tab10_pending_case_select_query->execute();
                                       

                                     /* $query_tab_10=db_query('select  *  from labour_factory_statcell_annual_report_t9_10 where  annual_inspection_id = :anid and is_pending  = :ispen', array(':anid' => trim($filenumber) , ':ispen' => 1 ));*/


                                       $i=0;
		                          foreach($query_tab_10 as $squan) {
			                       $i++;
		                          $row_id = $squan->row_id; 
		                          $annual_inspection_id = $squan->annual_inspection_id; 
	                              $factory_name=$squan->factory_name; 
			                      $factory_address=$squan->factory_address;     
			                      $reg_unreg=$squan->reg_unreg;   
                                  $person_prosecuted=$squan->person_prosecuted; 
                                  $case_number=$squan->case_number;  

            
                                  $court_name=$squan->court_name;  
                                  $violation_description=$squan->violation_description; 
                                  $results=$squan->results; 
                                  $total_fine=$squan->total_fine; 
                                   $case_date = !(trim($squan->case_date)) ?  '' :  date('d-m-Y', strtotime($squan->case_date));

                                 $content .= '<tr>

                                   
				                   <td align="center" valign="middle"   >'.$factory_name.'</td>
			                       <td align="center" valign="middle"   >'.$factory_address.'</td>
                                   <td align="center" valign="middle"   >'.$reg_unreg.'</td>
                                   <td align="center" valign="middle"   >'.$person_prosecuted.'</td>
                                   <td align="center" valign="middle"   >'.$case_number.'</td>
                                   <td align="center" valign="middle"   >'.$court_name.'</td>
                                   <td align="center" valign="middle"   >'.$violation_description.'</td>
                                    <td align="center" valign="middle"   >'.$results.'</td>
                                   <td align="center" valign="middle"   >'.$case_date.'</td>
                                   <td align="center" valign="middle"   >'.$total_fine.'</td>
                                   
			
				
			                     </tr>';
              
			   
	                             }


                                    $content .= '  </table></div>



                                        <div class="table-panel-header"><b> 11. </b></div>
                                          <div class="table-responsive">
                     					<table class="table table-striped table-bordered table-responsive admin-custom-table">';


                                          	 $step11_select_query = db_select('labour_factory_statcell_annual_report_t11', 'a');
       
                                            $step11_select_query->condition('a.annual_inspection_id',trim($filenumber),'=');
      
		
                                            $step11_select_query->fields('a',array('case_pending_at_beginning','case_disposed_of_during','case_pending_at_end','special_studies','seminar_training_courses','other_activities'));
                                            $step11_select_query_result = $step11_select_query->execute(); 
		
		                                    $result_step11=$step11_select_query_result->fetchAssoc();
		                                    
      
                                              
                                             
      
                                             
                                         $content .= '  <tr> <td align="left" valign="middle"  > 11.(a) No.of cases pending at the beginning of the year</td>  <td> '.$result_step11['case_pending_at_beginning'] .'</td></tr>
                                           <tr> <td align="left" valign="middle"  > 11.(b) No.of cases disposed of during the year -</td>  <td>'.$result_step11['case_disposed_of_during'] .'</td></tr>
                                           <tr> <td align="left" valign="middle"  > 11.(C) No.of cases pending at the end of the year -</td>  <td>'.$result_step11['case_pending_at_end'] .'</td></tr>
                                           <tr> <td align="left" valign="middle"  > 12. Details of special studies conducted.</td>  <td>'.$result_step11['special_studies'] .'</td></tr>
                                           <tr><td align="left" valign="middle"  > 13. Details of seminar,training courses, etc conducted.</td>  <td>'.$result_step11['seminar_training_courses'] .'</td></tr>
                                          <tr>  <td align="left" valign="middle"  > 14. Details of other activities, worth mentioning.</td>  <td>'.$result_step11['other_activities'] .'</td></tr>

                                            
                                            
                                            
                                             




                                      </table></div>

                                       <div class="table-panel-header"><b> A. Construction Works Details </b></div>';

                                           
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
		                                 




                                           $content .= '<div class="table-responsive">
                     					<table class="table table-striped table-bordered table-responsive admin-custom-table">
                                      
                                             <tr> <td align="left" valign="middle"  > 1.Number of units visited</td>  <td> '.$result_step2a['unit_visited'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > 2. Number of visits paid</td>  <td>'.$result_step2a['visit_paid'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > 3. Total number of violations observed</td>  <td>'.$result_step2a['violation'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > 4. No of Accidents </td>  <td>'.$result_step2a['accident'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > a) Fatal.</td>  <td>'.$result_step2a['fatal'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > b) Serious.</td>  <td>'.$result_step2a['serious'] .'</td></tr>

                                           <tr> <td align="left" valign="middle"  > 5.No of visits paid in connection with accidents</td>  <td>'.$result_step2a['connection_accident'] .'</td></tr>

                                         <tr> <td align="left" valign="middle"  > 6. No of complaints received</td>  <td>'.$result_step2a['complaints'] .'</td></tr>
                                        <tr> <td align="left" valign="middle"  > 7. No of visits paid in connection with complaints</td>  <td>'.$result_step2a['connection_complaints'] .'</td></tr>

                                           <tr> <td align="left" valign="middle"  > 8. No. of prosecution launched</td>  <td>'.$result_step2a['prosecution'] .'</td></tr></table>

                                          <div class="table-panel-header"><b> B.Construction Works Case Details </b></div>';



                                          $query_tab_12_b=db_query('select  *  from labour_factory_statcell_annual_report_attach_construct_t2 where  annual_inspection_id = :anid', array(':anid' => trim($filenumber) ));


                                          $content .= '
                                              <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
					 						<thead>
                                             <tr> 
                                           
                                            <th  valign="middle"  > Case No.</th>
                                            <th  valign="middle"  > Violation</th>
                                            <th  valign="middle"  > Court</th>
                                            <th  valign="middle"  > Remarks</th>
                                           
                                            
                                            
                                          </tr></thead>';

                                          foreach($query_tab_12_b as $squan) {
			
		                                 $annual_inspection_id = $squan->annual_inspection_id; 
	                                     $case_no=$squan->case_no;
			                             $violation=$squan->violation;
			                             $court=$squan->court;
                                         $remarks=$squan->remarks;

                                       $content .= '<tr>
				                   
				                  
				                   <td  valign="middle"   >'.$case_no.'</td>
			                       <td  valign="middle"   >'.$violation.'</td>
                                   <td  valign="middle"   >'.$court.'</td>
                                   <td  valign="middle"   >'.$remarks.'</td>
                                  
			                     
                                   </tr>';
			
				                   
			
              
			                       
	                             }

	                         $content .= '</table></div>

                             <div class="table-panel-header"><b> Maternity Benefits Act Rules </b></div>

                              <div><b> 1.No. of violations in respect of </b></div>

                              <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                      ';


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

                                             $content .= ' <tr> <td align="left" valign="middle"  > a) Display of the Abstract of the Act and the Rules</td>  <td> '.$result_step12c['no_act_and_rules_1_a'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > b) Non-maintenance of muster roll</td>  <td>'.$result_step12c['no_non_maintenance_muster_roll_1_b'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > c) Improper maintenance of muster roll</td>  <td>'.$result_step12c['no_imp_maintenance_1_c'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > d) Payment of maternity benefits </td>  <td>'.$result_step12c['maternity_benefit_1_d'] .'</td></tr>
                                            <tr> <td align="left" valign="middle"  > e)Others</td>  <td>'.$result_step12c['others_1_e'] .'</td></tr>
                                            </table> </div>

                                         <div class="table-panel-header"><b> 2. No. of compaints settled after investigation </b></div>
                                            
                                     
                                      <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                      <thead>
                                             <tr> 
                                            <th align="center" valign="middle"  > &nbsp;</th>
                                            <th align="center" valign="middle"  > Number.</th>
                                            <th align="center" valign="middle"  > Investigated</th>
                                            <th align="center" valign="middle"  > Violation observed</th>
                                            <th align="center" valign="middle"  > Action taken</th>
                                            <th align="center" valign="middle"  > Remarks</th>
                                           
                                            
                                            
                                          </tr></div>

                                        <tr>
				                  
				                   <td align="center" valign="middle"   > Regd. factories </td>
			                       <td align="center" valign="middle"   >'.$result_step12c['regd_number_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['reg_investigate_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['reg_violation_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['reg_action_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['reg_remarks_2'].'</td>
                                  </tr>
                                  <tr>

                                   <td align="center" valign="middle"   > Un-regd. factories </td>
			                       <td align="center" valign="middle"   >'.$result_step12c['unreg_number_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['unreg_investigate_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['unreg_violation_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['unreg_action_2'].'</td>
                                   <td align="center" valign="middle"   >'.$result_step12c['unreg_remarks_2'].'</td>
                                  
			                     
                                   </tr>
                               </table></div>
								
							

                                      ';



                             $query_tab_12_d=db_query('select  *  from labour_factory_statcell_annual_report_attach_maternity_wages where  maternity_wages_id = :anid and maternity_wages_type = :mwt', array(':anid' => trim($filenumber) , ':mwt' => 'MATERNITY'));
     
      $content .= ' 

       <div><b> 3. Maternity Benefit Case Details </b></div>
      <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
					 <thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the factory. </th>
	    <th >Section-Rules violated </th>
       
		 <th >Case No.</th>

		 <th >Amount of fines posted</th>
       
		 <th >Remarks</th>

		 
		
		</tr></thead>';  
			  $i=0;
		foreach($query_tab_12_d as $squan) {
			$i++;
		      $row_id = $squan->row_id; 
		      $maternity_wages_id = $squan->maternity_wages_id; 
	          $maternity_wages_type=$squan->maternity_wages_type;



	            $content .= ' <tr >
				
				<td>'.$i.'</td> 
				<td>'.$squan->factory_name_3.'</td>
			    <td>'.$squan->section_rules_3.'</td>
                <td>'.$squan->case_number_3.'</td>
                <td>'.$squan->amount_fine_3.'</td>
                <td>'.$squan->remarks_3.'</td>
               
			
				
			
              
			 </tr>';
	        }
              $content .= '</table></div>
            
              <div class="table-responsive">
                             <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                <div><b> 4. a) No. of case pending at the beginning of the year </b> '.$result_step12c['case_pending_at_beginning_4_a'].'</div>
                                <div><b> b) No. of case in disposed off during the year </b> '.$result_step12c['case_disposed_4_b'].'</div>
                                 <div><b> c) No. of case pending at the end of the year </b> '.$result_step12c['case_pending_at_end_4_c'].'</div></table></div>


                  <div><b> Payment of wages </b></div>
                   <div><b> Information relating to payment of Wages act & Rules </b></div> ';
                 

                  $step12e_query = db_select('labour_factory_statcell_annual_report_attach_wages_t1', 'd');
       
                  $step12e_query->condition('d.annual_inspection_id',trim($filenumber),'=');
      
		
                  $step12e_query->fields('d',array('no_act_and_rules_1_a',
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
        $step12e_query_result = $step12e_query->execute(); 
		 
		$result_step2e=$step12e_query_result->fetchAssoc();
                 $content .= '   
                 <div class="table-panel-header"><b> 1. No. of violations in respect of </b></div>
                 <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
                 <tr> <td align="left" valign="middle"  > a) Display of the Abstract of the Act and the Rules</td>  <td> '.$result_step2e['no_act_and_rules_1_a'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (b) Display of the notice of dates of payment</td>  <td>'.$result_step2e['no_notice_dates_payment_1_b'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (c) Non-maintenance of register of wages</td>  <td>'.$result_step2e['no_non_maintenance_wages_1_c'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (d) Improper maintenance of register of wages </td>  <td>'.$result_step2e['no_imp_maintenance_wages_1_d'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (e) Irregularities in recording dates of payment</td>  <td>'.$result_step2e['no_recording_date_payment_1_e'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (f)Non-availability of register of wages </td>  <td>'.$result_step2e['no_register_wages_1_f'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (g) Delayed wages</td>  <td>'.$result_step2e['no_delayed_wages_1_g'] .'</td></tr>
                 <tr> <td align="left" valign="middle"  > (h) Others </td>  <td>'.$result_step2e['no_others_1_h'] .'</td></tr>





            </table> </div>
                                            
                 <div class="table-panel-header"><b> 2. No. of complaints settled after investigation </b></div>

                   <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                      <thead>
                 <tr> <th > &nbsp; </th>
	              <th >Number </th>
       
		        <th >Investigated.</th>

		        <th >Violation observed</th>
       
		        <th >Action taken</th>
               <th >Remarks</th>
               </tr></thead>
                <tr>
               	<td align="left" valign="middle"  >Regd. factories </td>
                <td align="left" valign="middle"  >'.$result_step2e['regd_number_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['reg_investigate_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['reg_violation_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['reg_action_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['reg_remarks_2'] .' </td>
                </tr>

                <tr>
               	<td align="left" valign="middle"  >  Un-regd. factories </td>
                <td align="left" valign="middle"  >'.$result_step2e['unreg_number_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['unreg_investigate_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['unreg_violation_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['unreg_action_2'] .' </td>
                <td align="left" valign="middle"  >'.$result_step2e['unreg_remarks_2'] .' </td>
                </tr>




                </table></div>';
                 $query_tab_12_f=db_query('select  *  from labour_factory_statcell_annual_report_attach_maternity_wages where  maternity_wages_id = :anid and maternity_wages_type = :mwt', array(':anid' => trim($filenumber) , ':mwt' => 'WAGES'));
    
       $content .= ' <div class="table-responsive">
                     <table class="table table-striped table-bordered table-responsive admin-custom-table">
                                      <thead>
	    <tr > <th >SL.NO</th>
      
       <th > Name of the factory. </th>
	    <th >Section-Rules violated </th>
       
		 <th >Case No.</th>

		 <th >Amount of fines posted</th>
       
		 <th >Remarks</th>
       	</tr></thead>';

       	foreach($query_tab_12_f as $squan) {
		 
		$content .= '<tr >
				
				<td>'.$i.'</td>
				<td>'.$squan->factory_name_3.'</td>
			    <td>'.$squan->section_rules_3.'</td>
                <td>'.$squan->case_number_3.'</td>
                <td>'.$squan->amount_fine_3.'</td>
                 <td>'.$squan->remarks_3.'</td>
               
			
				
              
			   </tr>';
	          }
              $content .= '</table></div>

			 
              <div class="table-panel-header"><b> 3. Prosecution </b></div>
			  <div class="table-responsive">
			  <table class="table table-striped table-bordered table-responsive admin-custom-table">
              <tr><td align="left" valign="middle"> a) No. of case pending at the beginning of the year - </td> <td>'.$result_step2e['case_pending_at_beginning_3_a'] .'</td></tr>
              <tr><td align="left" valign="middle"> b) No. of case in disposed off during the year- </td><td>'.$result_step2e['case_disposed_3_b'] .'</td></tr>
              <tr><td align="left" valign="middle"><b> c) No. of case pending at the end of the year- </td><td>'.$result_step2e['case_pending_at_end_3_c'] .'</td></tr></table></div>

              <div class="table-panel-header"><b> 4. Information regarding applications filed during the year before the authority under the P.W Act -</b></div>
			<div class="table-responsive">
			  <table class="table table-striped table-bordered table-responsive admin-custom-table">
              <tr><td align="left" valign="middle"> a. Name of the factories- </td><td> '.$result_step2e['factories_name_4_a'] .'</td></tr>
             <tr><td align="left" valign="middle"> b. Total number of applications filed- </td><td> '.$result_step2e['application_filed_4_b'] .'</td></tr>
             <tr><td align="left" valign="middle"> c. Total number of persons involved -</td><td> '.$result_step2e['person_involved_4_c'] .'</td></tr>
             <tr><td align="left" valign="middle"> d. Total amount of unpaid wages claimed- </td><td> '.$result_step2e['wages_claimed_4_d'] .'</td></tr>
             <tr><td align="left" valign="middle"> e. Total amount of un-authorised deductions claimed -</td><td> '.$result_step2e['deduction_claimed_4_e'] .'</td></tr>
             <tr><td align="left" valign="middle"> f. Number of applications pending at the beginning of the year- </td><td> '.$result_step2e['app_pending_at_beginning_4_f'] .'</td></tr>
             <tr><td align="left" valign="middle"> g. Number of applications disposed off during the year- </td><td> '.$result_step2e['app_disposed_4_g'] .'</td></tr>
             <tr><td align="left" valign="middle"> h. Number of applications pending at the end of the year -</td><td> '.$result_step2e['app_pending_at_end_4_h'] .'</td></tr></table></div>';

              
	
                          

           //print    $content;     


          $form['step13Bfield'] = array(
          '#title' => t('View & Submit'),
          '#type' => 'fieldset',
          '#collapsed' => FALSE
          );                         

       
                $form['step13Bfield']['col2'] = array
              (
                 '#prefix' => ' <div   >'.$content, 
               
           

                '#suffix'=>'',
       
       
           );  
              $form['step13Bfield']['inspectionid'] = 
               array('#type' => 'hidden',  
             '#value' => $filenumber,
       
            );

             
             $result_string = "'" . str_replace(",", "','", $area) . "'";

            
             $roleId=get_role_id($inspector_id);
           
             $role_name=get_role_name($roleId);
             //print 'sss'.$role_name;
             if($role_name=='factoryinspector')
                $deputy_cheif_role='deputychief';
             elseif($role_name=='factoryinspector_chemical')
                $deputy_cheif_role='deputychief_chemical';
            elseif($role_name=='factoryinspector_medical')
                $deputy_cheif_role='deputychief_medical';

           $options_dp =  anr_deputy_director_option($result_string , $deputy_cheif_role );
         
          $form['step13Bfield']['dp_director'] = array (
                    '#type' => 'select',
                    '#title' => ('Select Deputy'),
                    '#options'       => $options_dp,
                    
                    '#required' => TRUE,
                   //  '#multiple'     =>  true,
                   //   '#attributes' => array('style' => array('height: 100px; ')),
                
                   '#prefix'            => '<div> ',
                   '#suffix'            => '</div>',
                    //'#rows'        => 10,
               );


          $form['step13Bfield']['submit_button']                    = array(
                                                                 
                                                               '#prefix' => '<div style="text-align:center;"  >',
                                                                 '#suffix'=>'</div></div>', 
                                                                '#type'                 =>'submit',
                                                                '#value'                =>t(' Submit ')
                                                                );

           return $form;                                 

	//echo $content; die;	
	//$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 20, 10, 0, 0);
	//$mpdf->SetDisplayMode('fullpage');
	//$mpdf->SetHTMLHeader('
	//<div style="padding-top:50px; text-align: right; font-size:9px;">
		//Page {PAGENO} of {nb}
	//</div>');
	//$mpdf->SetWatermarkText('DRAFT COPY');
	//$mpdf->showWatermarkText = true;
	//$mpdf->WriteHTML($content);
	//$mpdf->Output('Worker-Information-Extension-'.time().'.pdf', 'I');
}

function annual_report_view_submit($form, &$form_state) {
   global $base_root, $base_path,$full_base;

      $full_base='';


      $val=$form_state['values'];
       //print_r($val);
       //exit;


    $inspectionid=trim($val['inspectionid']);
    $dp_director_uid=trim($val['dp_director']);

    $txn = db_transaction();
      try {
          
   


      $query_update_B = db_update('labour_factory_statcell_annual_report');
      $query_update_B->fields(array(
            'status' =>'FD', 'submit_date' => date("Y-m-d")  ,'is_submitted' => 1 , 'accept_by' => $dp_director_uid ));
                                        
                                        
                                        
       $query_update_B->condition('annual_inspection_id',$inspectionid);
       $query_update_B->execute(); 





    
    
       $message = '   Annual report submit successfully ';
     drupal_set_message(t($message));
     $full_base=$base_root.$base_path.'admin/annual-report-list';
               
    drupal_goto($full_base);
    
     }
    catch (Exception $e) {
    
    $txn->rollback();
  
    watchdog_exception('type', $e);
    $message = '    Annual report is not submit  ';
     drupal_set_message(t($message));

      $full_base=$base_root.$base_path.'admin/annual-report/step13/'.encryption_decryption_fun('encrypt',$autoGENNO);
               
    drupal_goto($full_base);
     }



   


}
function anr_deputy_director_option($area , $deputy_cheif_role) {
   

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

?>