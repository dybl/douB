<?php
/**
 * Template part for displaying posts.
 *
 * @link https://codex.wordpress.org/Template_Hierarchy
 *
 * @package Akina
 */

?>

<article id="post-<?php the_ID(); ?>" <?php post_class(); ?>>
	<header class="entry-header">
		<h1 class="entry-title"><?php the_title(); ?></h1>
		<hr>
	<div class="breadcrumbs">	
	<?php if(function_exists('cmp_breadcrumbs')) cmp_breadcrumbs();?>
    </div>	
	</header><!-- .entry-header -->

	<div class="entry-content">
		<?php the_content(); ?>
		<?php
			wp_link_pages( array(
				'before' => '<div class="page-links">' . __( 'Pages:', 'akina' ),
				'after'  => '</div>',
			) );
		?>
	</div><!-- .entry-content -->

	<footer class="post-footer">
    <?php get_template_part('inc/sharelike'); ?>	
	</footer><!-- .entry-footer -->
</article><!-- #post-## -->
