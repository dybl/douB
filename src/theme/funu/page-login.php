<?php 

	/**
	 Template Name: login
	 */
	 wp_head();
?>
<div class="login-main">
	<div class="login-box">
	<div class="login_inner">
		<?php if (!(current_user_can('level_0'))){ ?>
			<a href="<?php bloginfo('url');?>"><img src="<?php echo akina_option('akina_logo', 'http://7xwpo4.com1.z0.glb.clouddn.com/akina3.png'); ?>"/></a>
			<form action="<?php echo get_option('home'); ?>/wp-login.php" id="loginform" method="post">
			<input type="text" name="log" id="log" value="<?php echo wp_specialchars(stripslashes($user_login), 1) ?>" size="20" />
			<input type="password" name="pwd" id="pwd" size="20" />
			<input type="submit" name="submit" value="Login" class="loginbutton" />
			<p>
			<input type="hidden" name="redirect_to" value="<?php echo $_SERVER['REQUEST_URI']; ?>" />
			</p>
			</form>
			<a id="forget" href="<?php echo get_option('home'); ?>/wp-login.php?action=lostpassword">Forget your password?</a>
			<?php } else { 
			 wp_redirect( home_url() ); exit; //如果已经登录，重定向到站点首页  
		 }?>
		</div>	
		</div>	
</div>		


<style type="text/css">
body {
    margin: 0px;
}
</style>