<?php
/**
 * The template for displaying all single posts.
 *
 * @link https://developer.wordpress.org/themes/basics/template-hierarchy/#single-post
 *
 * @package Akina
 */

get_header(); ?>

	<div id="primary" class="content-area">
		<main id="main" class="site-main" role="main">

		<?php
		while ( have_posts() ) : the_post();

			get_template_part( 'template-parts/single', get_post_format() );
			
			get_template_part('layouts/copyright');

			get_template_part('layouts/post-nextprev'); 
			
		    get_template_part('layouts/authorprofile'); 


		endwhile; // End of the loop.
		?>

		</main><!-- #main -->
	</div><!-- #primary -->
	

<?php
get_sidebar();
get_footer();
