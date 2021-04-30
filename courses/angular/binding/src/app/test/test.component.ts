import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-test',
  template: `
    <h2> Welcome {{name}} </h2>       <!Interpulation>
    <h2> {{2+2}} </h2>                <!Evaluation> 
    <h2> {{"Welcome " + name}} </h2>  <!Concatenation>
    <h2> {{name.length}} </h2>
    <h2> {{name.toUpperCase()}} </h2>
    <h2> {{greetUser()}} </h2>
    <h2> {{siteUrl}} </h2>            <!Binding global vars>
    `,
  styleUrls: ['./test.component.css']
})
export class TestComponent implements OnInit {

  public name = "Yaron";
  public siteUrl = window.location.href;
  constructor() { }

  ngOnInit(): void {
  }

  greetUser(){
    return "Hello " + this.name;
  }
}
