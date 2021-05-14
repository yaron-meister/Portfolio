import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-class-binding',
  template: `
  <h2>
    <br>
    Welcome to {{cBName}}
  </h2>
  <h2 class="text-success"> SUCCESS </h2>
  <h2 [class]="successClass"> SUCCESS 2 </h2> <!class-binding>
  <h2 [class.text-danger]="hasError"> ANSWER </h2> <!Conditionally apllied class>

  <h2 [ngClass]="messageClasses"> NG Classes </h2> <!NG Classes>
  `,
  styles: [`
    .text-success{
      color: green;
    }
    .text-danger{
      color: red;
    }
    .text-special{
      font-style: italic;
    }
  `]
})
export class ClassBindingComponent implements OnInit {

  public cBName = "CLASS-BINDING";
  public successClass = "text-success";
  public hasError = true;
  public isSpecial = true;
  public messageClasses = {
    "text-success": !this.hasError,
    "text-danger": this.hasError,
    "text-special": this.isSpecial
  }

  constructor() { }

  ngOnInit(): void {
  }

}
