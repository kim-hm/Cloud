package com.example.hellpofirebase;


import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class MainActivity extends AppCompatActivity {
    WebView webView;
    WebSettings WebSettings; //웹뷰세팅

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        webView = (WebView)findViewById(R.id.webView);

        WebSettings = webView.getSettings(); //세부 세팅 등록
        WebSettings.setJavaScriptEnabled(true); // 웹페이지 자바스크립트 허용 여부
        WebSettings.setLoadWithOverviewMode(true); // 메타태그 허용 여부
        WebSettings.setUseWideViewPort(true); // 화면 사이즈 맞추기 허용 여부
        WebSettings.setSupportZoom(false); // 화면 줌 허용 여부
        WebSettings.setBuiltInZoomControls(false); // 화면 확대 축소 허용 여부
        // 컨텐츠 사이즈 맞추기
        WebSettings.setLayoutAlgorithm(android.webkit.WebSettings.LayoutAlgorithm.SINGLE_COLUMN);
        //파일 경로 지정해주기
        String webUrlLocal = "file:///C:/APM_Setup/htdocs/test/index2.html";
        webView.loadUrl(webUrlLocal);

    }
}