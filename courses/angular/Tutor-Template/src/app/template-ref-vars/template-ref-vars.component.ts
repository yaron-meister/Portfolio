import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-template-ref-vars',
  template: `
  <h2>
    Welcome to {{templateRefVarsCompName}}
  </h2>
  <input #myInput type="text">
  <button (click)="logMessage(myInput.value)"> Log </button> 
  <! Passing the Input value (here it's the text) by the button click> 
  <! # symbol is the reference operator which is followed by the var name>
  <button (click)="logMessage(myInput)"> Passing the reference </button> <! Passing the Input reference by the button click> 
  `,
  styles: []
})
export class TemplateRefVarsComponent implements OnInit {

  public templateRefVarsCompName = "TEMPLATE-REFERENCE-VARIABLES";

  constructor() { }

  ngOnInit(): void {
  }

  logMessage(value){
    console.log(value);
  }
}
