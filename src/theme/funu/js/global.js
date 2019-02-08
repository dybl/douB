/**
 * global js
 */
 
 
//ajax评论
var ajaxcomments = function(){
	var edit_mode = '0', // 再編輯模式 ( '1'=開; '0'=不開 )
		//ajax_php_url = ajaxcomment.ajax_url,
		wp_url = window.location.href,
		pic_sb = wp_url + 'wp-admin/images/wpspin_light.gif', // 提交 icon
		pic_no = wp_url + 'wp-admin/images/no.png',      // 錯誤 icon
		pic_ys = wp_url + 'wp-admin/images/yes.png',     // 成功 icon
		txt1 = '<div id="loading"><span class="err-ti"></span> 正在提交, 请稍候...</div>',
		txt2 = '<div id="error">#</div>',
		txt3 = '"><span class="submit-su"></span> 提交成功',
		edt1 = ', 刷新页面之前可以<a rel="nofollow" class="comment-reply-link" href="#edit" onclick=\'return addComment.moveForm("',
		edt2 = ')\'>再编辑</a>',
		cancel_edit = '取消编辑',
		edit, num = 1, comm_array=[]; comm_array.push('');

	$comments = $('#comments-title'); // 評論數的 ID
		$cancel = $('#cancel-comment-reply-link'); cancel_text = $cancel.text();
		$submit = $('#commentform #submit'); $submit.attr('disabled', false);
		$('#comment').after( txt1 + txt2 ); $('#loading').hide(); $('#error').hide();
		$body = (window.opera) ? (document.compatMode == "CSS1Compat" ? $('html') : $('body')) : $('html,body');

	/** submit */
	$('#commentform').submit(function() {
		$('#loading').slideDown();
		$submit.attr('disabled', true).fadeTo('slow', 0.5);
		if ( edit ) $('#comment').after('<input type="text" name="edit_id" id="edit_id" value="' + edit + '" style="display:none;" />');

	/** Ajax */
	$.ajax( {
		url: app.ajax_url,
		data: $(this).serialize() + "&action=ajax_comment_post",
		type: $(this).attr('method'),

		error: function(request) {
			$('#loading').slideUp();
			$('#error').slideDown().html('<span class="submit-er"></span> ' + request.responseText);
			setTimeout(function() {$submit.attr('disabled', false).fadeTo('slow', 1); $('#error').slideUp();}, 1500);
			},

		success: function(data) {
			$('#loading').hide();
			comm_array.push($('#comment').val());
			$('textarea').each(function() {this.value = ''});
			var t = addComment, cancel = t.I('cancel-comment-reply-link'), temp = t.I('wp-temp-form-div'), respond = t.I(t.respondId), post = t.I('comment_post_ID').value, parent = t.I('comment_parent').value;

// comments
		if ( ! edit && $comments.length ) {
			n = parseInt($comments.text().match(/\d+/));
			$comments.text($comments.text().replace( n, n + 1 ));
		}

// show comment
		new_htm = '" id="new_comm_' + num + '"></';
		new_htm = ( parent == '0' ) ? ('\n<ol style="clear:both;" class="commentwrap' + new_htm + 'ol>') : ('\n<ul class="children' + new_htm + 'ul>');

		ok_htm = '\n<span id="success_' + num + txt3 ;
		if ( edit_mode == '1' ) {
			div_ = (document.body.innerHTML.indexOf('div-comment-') == -1) ? '' : ((document.body.innerHTML.indexOf('li-comment-') == -1) ? 'div-' : '');
			ok_htm = ok_htm.concat(edt1, div_, 'comment-', parent, '", "', parent, '", "respond", "', post, '", ', num, edt2);
		} 
		ok_htm += ' </span><span></span>\n';

		$('#respond').before(new_htm);
		$('#new_comm_' + num).hide().append(data);
		$('#new_comm_' + num + ' li').append(ok_htm);
		$('#new_comm_' + num).fadeIn(600);

		$body.animate( { scrollTop: $('#new_comm_' + num).offset().top - 200}, 900);
		countdown(); num++ ; edit = ''; $('*').remove('#edit_id');
		cancel.style.display = 'none';
		cancel.onclick = null;
		t.I('comment_parent').value = '0';
		if ( temp && respond ) {
			temp.parentNode.insertBefore(respond, temp);
			temp.parentNode.removeChild(temp)
		}
		}
	}); // end Ajax
  	return false;
  	}); // end submit

	/** comment-reply.dev.js */
	addComment = {
		moveForm : function(commId, parentId, respondId, postId, num) {
			var t = this, div, comm = t.I(commId), respond = t.I(respondId), cancel = t.I('cancel-comment-reply-link'), parent = t.I('comment_parent'), post = t.I('comment_post_ID');
			if ( edit ) exit_prev_edit();
			num ? (
				t.I('comment').value = comm_array[num],
				edit = t.I('new_comm_' + num).innerHTML.match(/(comment-)(\d+)/)[2],
				$new_sucs = $('#success_' + num ), $new_sucs.hide(),
				$new_comm = $('#new_comm_' + num ), $new_comm.hide(),
				$cancel.text(cancel_edit)
			) : $cancel.text(cancel_text);

			t.respondId = respondId;
			postId = postId || false;

			if ( !t.I('wp-temp-form-div') ) {
				div = document.createElement('div');
				div.id = 'wp-temp-form-div';
				div.style.display = 'none';
				respond.parentNode.insertBefore(div, respond)
			}

			!comm ? ( 
				temp = t.I('wp-temp-form-div'),
				t.I('comment_parent').value = '0',
				temp.parentNode.insertBefore(respond, temp),
				temp.parentNode.removeChild(temp)
			) : comm.parentNode.insertBefore(respond, comm.nextSibling);

			$body.animate( { scrollTop: $('#respond').offset().top - 180 }, 400);

			if ( post && postId ) post.value = postId;
			parent.value = parentId;
			cancel.style.display = '';

			cancel.onclick = function() {
				if ( edit ) exit_prev_edit();
				var t = addComment, temp = t.I('wp-temp-form-div'), respond = t.I(t.respondId);

				t.I('comment_parent').value = '0';
				if ( temp && respond ) {
					temp.parentNode.insertBefore(respond, temp);
					temp.parentNode.removeChild(temp);
				}
				this.style.display = 'none';
				this.onclick = null;
				return false;
			};

			try { t.I('comment').focus(); }
			catch(e) {}

			return false;
		},

		I : function(e) {
			return document.getElementById(e);
		}
	}; // end addComment

	function exit_prev_edit() {
		$new_comm.show(); $new_sucs.show();
		$('textarea').each(function() {this.value = ''});
		edit = '';
	};

	var wait = 15, submit_val = $submit.val();
	function countdown() {
		if ( wait > 0 ) {
			$submit.val(wait); wait--; setTimeout(countdown, 1000);
		} else {
			$submit.val(submit_val).attr('disabled', false).fadeTo('slow', 1);
			wait = 15;
	  }
	};

 } 

//表情 
function grin(tag) {
    	var myField;
    	tag = ' ' + tag + ' ';
        if (document.getElementById('comment') && document.getElementById('comment').type == 'textarea') {
    		myField = document.getElementById('comment');
    	} else {
    		return false;
    	}
    	if (document.selection) {
    		myField.focus();
    		sel = document.selection.createRange();
    		sel.text = tag;
    		myField.focus();
    	}
    	else if (myField.selectionStart || myField.selectionStart == '0') {
    		var startPos = myField.selectionStart;
    		var endPos = myField.selectionEnd;
    		var cursorPos = endPos;
    		myField.value = myField.value.substring(0, startPos)
    					  + tag
    					  + myField.value.substring(endPos, myField.value.length);
    		cursorPos += tag.length;
    		myField.focus();
    		myField.selectionStart = cursorPos;
    		myField.selectionEnd = cursorPos;
    	}
    	else {
    		myField.value += tag;
    		myField.focus();
    	}
    } 

//nav show/hidden
$(function(){
	var h1 = 0;
	var h2 = 50;
	var ss = $(document).scrollTop();
	$(window).scroll(function(){
		var s = $(document).scrollTop();

		if(s== h1){
			$('.site-header').removeClass('yya');
		}if(s > h1){
			$('.site-header').addClass('yya');
		}if(s > h2){
			$('.site-header').addClass('gizle');
			if(s > ss){
				$('.site-header').removeClass('sabit');
			}else{
				$('.site-header').addClass('sabit');
			}
			ss = s;
		}


	});
	
});
 
//mo-nav
var mNav = function(){
	$('.iconflat').on('click', function () {
	    $('body').toggleClass('navOpen');
	    $('#main-container,#mo-nav,.openNav').toggleClass('open');
	});
}
var mNav_hide = function(){
	if($('body').hasClass('navOpen')){
   		$('body').toggleClass('navOpen');
	    $('#main-container,#mo-nav,.openNav').toggleClass('open');
   	}
}

/*
 * AJAX Single
*/
var loadSingle = function(){
	$("#pagination a").live("click", function(){
	    $(this).addClass("loading").text("");
	    $.ajax({
		type: "POST",
	        url: $(this).attr("href") + "#main",
	        success: function(data){
	            result = $(data).find("#main .post");
	            nextHref = $(data).find("#pagination a").attr("href");
	            // In the new content
	            $("#main").append(result.fadeIn(300));
	            $("#pagination a").removeClass("loading").text("加载更多");
	            if ( nextHref != undefined ) {
	                $("#pagination a").attr("href", nextHref);
	            } else {
	            // If there is no link, that is the last page, then remove the navigation
	                $("#pagination").remove();
	            }
	        }
	    });
	    return false;
	});
}
	

// 评论分页
$body=(window.opera)?(document.compatMode=="CSS1Compat"?$('html'):$('body')):$('html,body');
// 点击分页导航链接时触发分页
$('#comments-navi a').live('click', function(e){
    e.preventDefault();
    $.ajax({
        type: "GET",
        url: $(this).attr('href'),
        beforeSend: function(){
            $('#comments-navi').remove();
            $('ul.commentwrap').remove();
            $('#loading-comments').slideDown();
            $body.animate({scrollTop: $('#comments-list-title').offset().top - 65}, 800 );
        },
        dataType: "html",
        success: function(out){
            result = $(out).find('ul.commentwrap');
            nextlink = $(out).find('#comments-navi');
            $('#loading-comments').slideUp('fast');
            $('#loading-comments').after(result.fadeIn(500));
            $('ul.commentwrap').after(nextlink);
        }
    });
});

// 顶部加载条
var loading = function(){
	
//preloading
$(window).preloader({	
		        delay: 500
		    });	
}

/*
 * Click Event  防止一些点击事件因为而pjax失效  代码取自路易
*/
var clickEvent = function(){
	
	ajaxcomments();
//表情js	
  $(".smli-button").click(function(){
    $(".smilies-box").fadeToggle("fast");
  });


//comment-author-info-toggle akina-1.05
$("#toggle-comment-info").click(function(){
    $("#comment-author-info").slideToggle("slow");
  });

//打赏 8.15
  $(".donate").click(function(){
    $(".donate_inner").fadeToggle("fast");
  });
 
// Archives Page
	$('.archives').hide();
	$('.archives:first').show();
	$('#archives-temp h3').click(function() {
		$(this).next().slideToggle('fast');
		return false;
	});

//lightbox

 baguetteBox.run('.entry-content', {
        captions: function(element) {
            // `this` == Array of current gallery items
            return element.getElementsByTagName('img')[0].alt;
        }
    });
//searchbox
 $('.js-toggle-search').on('click', function () {
    $('.js-toggle-search').toggleClass('is-active');
    $('.js-search').toggleClass('is-visible');
    });
	
// Show & hide comments
	$('.comments-hidden').show();
	$('.comments-main').hide();
	$('.comments-hidden').click(function(){
		$('.comments-main').slideDown(500);
		$('.comments-hidden').hide();
	});	
}

/*
 * Click Event end
*/

//gotop		
jQuery(document).ready(function($){
	// browser window scroll (in pixels) after which the "back to top" link is shown
	var offset = 100,
		//browser window scroll (in pixels) after which the "back to top" link opacity is reduced
		offset_opacity = 1200,
		//duration of the top scrolling animation (in ms)
		scroll_top_duration = 700,
		//grab the "back to top" link
		$back_to_top = $('.cd-top');

	//hide or show the "back to top" link
	$(window).scroll(function(){
		( $(this).scrollTop() > offset ) ? $back_to_top.addClass('cd-is-visible') : $back_to_top.removeClass('cd-is-visible cd-fade-out');
		if( $(this).scrollTop() > offset_opacity ) { 
			$back_to_top.addClass('cd-fade-out');
		}
	});

	//smooth scroll to top
	$back_to_top.on('click', function(event){
		event.preventDefault();
		$('body,html').animate({
			scrollTop: 0 ,
		 	}, scroll_top_duration
		);
	});
	
	
	//pjax
	if(app.pjax){
	$(document).pjax('a[target!=_top]', '#page', {
        	fragment: '#page', //主容器
        	timeout: 8000, // 8秒限时
	    }).on('pjax:send', function() {
			$('body').append('<div id="preloader"><div id="preloader-inner"></div></div>'); // 加载过度动画
	    }).on('pjax:complete', function() { // 加载完毕				
			clickEvent(); // 一些点击事件
			$('#preloader').remove(); // 删除过度动画				
			if ($('.ds-thread').length > 0) {  // 解决多说问题
	           if (typeof DUOSHUO !== 'undefined') 
	              DUOSHUO.EmbedThread('.ds-thread'); 
	           else 
	              $.getScript("//static.duoshuo.com/embed.js"); 
	        }   	
	    });
	}

});	


	
( function( $ ) {
// Load Function
loading();
clickEvent();
loadSingle();
mNav();

// Likes
$.fn.postLike = function() {
	if ($(this).hasClass('done')) {
		return false;
	} else {
		$(this).addClass('done');
		var id = $(this).data("id"),
		action = $(this).data('action'),
		rateHolder = $(this).children('.count');
		var ajax_data = {
			action: "specs_zan",
			um_id: id,
			um_action: action
		};
		$.post(app.ajax_url, ajax_data,
		function(data) {
			$(rateHolder).html(data);
		});
		return false;
	}
};
$(document).on("click", ".specsZan", function() {
	$(this).postLike();
});	

} )( jQuery );
	