<?php
/**
 * The template for displaying the footer.
 *
 * Contains the closing of the #content div and all content after.
 *
 * @link https://developer.wordpress.org/themes/basics/template-files/#template-partials
 *
 * @package Akina
 */

?>

	</div><!-- #content -->
	
	
	 <?php 
			if(akina_option('general_disqus_plugin_support')=='1'){
				get_template_part('layouts/duoshuo');
			}else{
				comments_template('', true); 
			}
	?>
			
	</div><!-- #page -->
	</section><!-- #section -->
	
	<footer id="colophon" class="site-footer" role="contentinfo">
		<div class="site-info">
			<?php esc_attr_e('Copyright ©', 'akina'); ?> <?php esc_attr_e(date('Y')); ?> by <?php bloginfo('name');?> <?php esc_attr_e('. All rights reserved.', 'akina'); ?>
			<span class="sep"> | </span>
			<!-- ！！！！！！！！！！！！请尊重作者，此主题免费，请不要修改版权，谢谢 -->
			<?php printf( esc_html__( 'Theme: %1$s by %2$s.', 'akina' ), 'Akina', '<a href="http://www.akina.pw" rel="designer">Fuzzz</a>' ); ?>
			<div class="footertext">
			<p><?php echo akina_option('footer_info', ''); ?></p>
			</div>
		</div><!-- .site-info -->
	</footer><!-- #colophon -->
	
	<!-- #mobile nav -->
	<div id="mo-nav">
		<div class="m-avatar">
			<?php $ava = akina_option('focus_logo') ? akina_option('focus_logo') : get_template_directory_uri().'/images/avatar2.jpg'; ?>
			<img src="<?php echo $ava ?>">
		</div>
		<div class="m-search">
			<form class="m-search-form" method="get" action="<?php echo home_url(); ?>" role="search">
				<input class="m-search-input" type="search" name="s" placeholder="<?php _e('搜索...', 'akina') ?>" required>
			</form>
		</div>
		<?php wp_nav_menu( array( 'depth' => 2, 'theme_location' => 'primary', 'container' => false ) ); ?>
	</div>

	<!-- #go top -->
	<div class="cd-top-box">
	<a href="#" class="cd-top"></a>
	</div>

    <!-- search start -->
	  <form class="js-search search-form search-form--modal" method="get" action="<?php echo home_url(); ?>" role="search">
		<div class="search-form__inner">
			<div>
				<p class="micro mb-"><?php _e('你想搜索什么...', 'akina') ?></p>
				<i class="iconfont">&#xe6f0;</i>
				<input class="text-input" type="search" name="s" placeholder="<?php _e('', 'akina') ?>">
			</div>
		</div>
	</form>
	<!-- search end -->
<!-- preloader -->
	<div id="preloader">
	    <div id="preloader-inner"></div>
	</div>
<?php wp_footer(); ?>
<?php if(akina_option('site_statistics')){ ?>
<div class="site-statistics">
<script type="text/javascript"><?php echo akina_option('site_statistics'); ?></script>
</div>
<?php } ?>

</body>
</html>
