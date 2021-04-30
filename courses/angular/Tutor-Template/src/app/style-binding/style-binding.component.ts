import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-style-binding',
  template: `
  <h2>
    Welcome to {{styleBindingCompName}}
  </h2>
  <h2 [style.color]="'orange'"> Style Binding </h2> <!Style-binding example>
  <h2 [style.color]="sBHasError ? 'red' : 'green'"> Style Binding 2 </h2> <!Conditional style-binding>
  <h2 [style.color]="highlightedColor"> Style Binding 3 </h2> 
  <h2 [ngStyle]="titleStyles"> NG Styles </h2>  <!NG Styles>
  `,
  styles: []
})
export class StyleBindingComponent implements OnInit {

  public styleBindingCompName = "STYLE-BINDING";
  public sBHasError = false;
  public highlightedColor = "orange";
  public titleStyles = {
    color: "blue",
    fontStyle: "italic"
  }

  constructor() { }

  ngOnInit(): void {
  }

}
