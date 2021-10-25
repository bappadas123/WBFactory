<?php
function cmsmanager_dashboard($form, &$form_state) {
	global $user;
   /****************************** Check IF Profile is Fillup or Not************************************************/
   $status = getUserProfileStatus($user->uid);
   if($status['one_time_pass_flag'] == '0') {
		drupal_goto('profileupdate');
		exit;
   }
   /********************************** End Profile is Fillup Cheaking************************************************/

}