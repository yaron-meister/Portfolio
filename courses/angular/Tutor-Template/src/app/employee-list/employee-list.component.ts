import { Component, OnInit } from '@angular/core';
import { EmployeeService } from '../employee.service';

@Component({
  selector: 'app-employee-list',
  template: `
  <h2>
    <br>
    Welcome to {{eLName}}
  </h2>
  <ul *ngFor="let employee of employees">
    <li>{{employee.name}}</li>
  </ul>
  `,
  styles: []
})
export class EmployeeListComponent implements OnInit {

  public eLName = "EMPLOYEE-LIST";
  public employees = [];

  constructor(private _employeeService: EmployeeService) { }

  ngOnInit(): void {
    this.employees = this._employeeService.getEmployees();
  }

}
